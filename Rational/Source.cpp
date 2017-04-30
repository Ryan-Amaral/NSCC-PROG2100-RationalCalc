// The driver file to use the Rational class

#include "Rational.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <regex>
#include <sstream>
#include <vector>
using namespace std;

bool equationEntered; // stores if input for first fraction has mulitple rationals
char theOperator; // the operator if an equation was entered
string strEquation; // stores the equaiton as a string for easy access.

enum ValidateRationalCode {INVALID, BLANK, ONE_NUMBER, FULL_RATIONAL, ABCD_EQUATION, AB_EQUATION, ABC_EQUATION, ACD_EQUATION};

// Validates the string input to place it into Rational Number.
int validateRationalString(string input){
	string regx; // regix for string matching

	// check if input is blank (give 0/1)
	if (input.length() == 1 && input.find("0") == 0){
		return ValidateRationalCode::BLANK;
	}

	// check if input is just single number (give number/1)
	regx = "-{0,1}[1-9]\\d{0,4}";
	if (regex_match(input, regex(regx))){
		return ValidateRationalCode::ONE_NUMBER;
	}

	// check if input is whole Rational number (give what they entered)
	regx = "-{0,1}[1-9]\\d{0,4}\\/-{0,1}[1-9]\\d{0,4}";
	if (regex_match(input, regex(regx))){
		return ValidateRationalCode::FULL_RATIONAL;
	}

	//check if input is equation with two Rationals A/B+C/D (solve then give answer)
	regx = "-{0,1}[1-9]\\d{0,4}\\/-{0,1}[1-9]\\d{0,4}[+\\-*\\/]-{0,1}[1-9]\\d{0,4}\\/-{0,1}[1-9]\\d{0,4}";
	if (regex_match(input, regex(regx))){
		return ValidateRationalCode::ABCD_EQUATION;
	}

	//check if input is equation with two Rationals A+B (solve then give answer)
	regx = "-{0,1}[1-9]\\d{0,4}[+\\-*]-{0,1}[1-9]\\d{0,4}"; // exclude / in operator because is just one rational
	if (regex_match(input, regex(regx))){
		return ValidateRationalCode::AB_EQUATION;
	}

	//check if input is equation with two Rationals A/B+C (solve then give answer)
	// if user enters for example (3/3/3) it will be interpreted as (3/3)/3, giving 1/3
	regx = "-{0,1}[1-9]\\d{0,4}\\/-{0,1}[1-9]\\d{0,4}[+\\-*\\/]-{0,1}[1-9]\\d{0,4}";
	if (regex_match(input, regex(regx))){
		return ValidateRationalCode::ABC_EQUATION;
	}

	//check if input is equation with two Rationals A+C/D (solve then give answer)
	regx = "-{0,1}[1-9]\\d{0,4}[+\\-*\\/]-{0,1}[1-9]\\d{0,4}\\/-{0,1}[1-9]\\d{0,4}";
	if (regex_match(input, regex(regx))){
		return ValidateRationalCode::ACD_EQUATION;
	}

	return ValidateRationalCode::INVALID;
}

// gives back an integer array containing the numbers needed for inserted rational
void getNumbersFromRationalString(string strRat, int ratCode, vector<int>& ratNums){
	stringstream strStrm; // need string stream to stream into int
	string tmpStr; // store the int as string to convert
	int index; // index of slash

	if (ratCode == ValidateRationalCode::FULL_RATIONAL){ // just one rational, split at slash
		// first number
		index = strRat.find_first_of("/");
		tmpStr = strRat.substr(0, index);
		strStrm << tmpStr;
		strStrm >> ratNums[0];

		strStrm.str(string());
		strStrm.clear();

		// second number, after slash
		tmpStr = strRat.substr(index + 1, strRat.length() - index - 1);
		strStrm << tmpStr;
		strStrm >> ratNums[1];
	}
	else if(ratCode == ValidateRationalCode::ABCD_EQUATION){ // four rationals, split at first and last slash
		// first number
		index = strRat.find_first_of("/");
		tmpStr = strRat.substr(0, index + 1);
		strStrm << tmpStr;
		strStrm >> ratNums[0];

		strStrm.str(string());
		strStrm.clear();

		// second number, after first slash
		tmpStr = strRat.substr(index + 1, strRat.length() - index - 1);
		strStrm << tmpStr;
		strStrm >> ratNums[1];

		strStrm.str(string());
		strStrm.clear();

		// third number, before last slash
		int spcIndex; // special index to help find third number
		// find index of operator
		for (int i = 1; i < tmpStr.length(); i++){ // start at second to skip negator
			if (!isdigit(tmpStr[i])){
				spcIndex = i;
				break;
			}
		}

		tmpStr = tmpStr.substr(spcIndex + 1, tmpStr.length() - spcIndex - 1);
		strStrm << tmpStr;
		strStrm >> ratNums[2];

		strStrm.str(string());
		strStrm.clear();

		// fourth number after last slash
		index = tmpStr.find_last_of("/");
		tmpStr = tmpStr.substr(index + 1, tmpStr.length() - index - 1);
		strStrm << tmpStr;
		strStrm >> ratNums[3];

	}
	else if (ratCode == ValidateRationalCode::AB_EQUATION){
		// no slashes

		int spcIndex; // special index to help find operator
		// find index of operator
		for (int i = 1; i < strRat.length(); i++){ // start at second to skip negator
			if (!isdigit(strRat[i])){
				spcIndex = i;
				break;
			}
		}

		tmpStr = strRat.substr(0, spcIndex + 1);
		strStrm << tmpStr;
		strStrm >> ratNums[0];

		strStrm.str(string());
		strStrm.clear();

		tmpStr = strRat.substr(spcIndex + 1, strRat.length() - spcIndex - 1);
		strStrm << tmpStr;
		strStrm >> ratNums[1];
	}
	else if (ratCode == ValidateRationalCode::ABC_EQUATION){
		// first number
		index = strRat.find_first_of("/");
		tmpStr = strRat.substr(0, index + 1);
		strStrm << tmpStr;
		strStrm >> ratNums[0];

		strStrm.str(string());
		strStrm.clear();

		// second number, after first slash
		tmpStr = strRat.substr(index + 1, strRat.length() - index - 1);
		strStrm << tmpStr;
		strStrm >> ratNums[1];

		strStrm.str(string());
		strStrm.clear();

		int spcIndex; // special index to help find operator
		// find index of operator
		for (int i = index + 1; i < strRat.length(); i++){ // start at second to skip negator
			if (!isdigit(strRat[i])){
				spcIndex = i;
				break;
			}
		}

		tmpStr = strRat.substr(spcIndex + 1, strRat.length() - spcIndex - 1);
		strStrm << tmpStr;
		strStrm >> ratNums[2];
	}
	else if (ratCode == ValidateRationalCode::ACD_EQUATION){
		int spcIndex; // special index to help find operator
		// find index of operator
		for (int i = 1; i < strRat.length(); i++){ // start at second to skip negator
			if (!isdigit(strRat[i])){
				spcIndex = i;
				break;
			}
		}

		tmpStr = strRat.substr(0, spcIndex + 1);
		strStrm << tmpStr;
		strStrm >> ratNums[0];

		strStrm.str(string());
		strStrm.clear();

		tmpStr = strRat.substr(spcIndex + 1, strRat.length() - spcIndex - 1);
		strStrm << tmpStr;
		strStrm >> ratNums[1];

		strStrm.str(string());
		strStrm.clear();

		index = strRat.find_last_of("/");
		tmpStr = strRat.substr(index + 1, tmpStr.length() - index - 1);
		strStrm << tmpStr;
		strStrm >> ratNums[2];
	}

	strStrm.str(string());
	strStrm.clear();
}

// friend function from Rational (input)
istream& operator >>(istream &input, Rational &rat){
	// put the input into a string
	string strInput;
	input >> strInput;
	stringstream strStrm(strInput);// put string into the string stream

	vector<int> ratNums(4);

	equationEntered = false;

	// the code for what the string is
	int validationCode = validateRationalString(strInput);

	// check if input is blank (give 0/1)
	if (validationCode == ValidateRationalCode::BLANK){
		rat = Rational();
	}

	// check if input is just single number (give number/1)
	if (validationCode == ValidateRationalCode::ONE_NUMBER){
		int num;
		strStrm >> num; // easily extract from stream
		rat = Rational(num);
	}

	// check if input is whole Rational number (give what they entered)
	if (validationCode == ValidateRationalCode::FULL_RATIONAL){
		getNumbersFromRationalString(strInput, validationCode, ratNums); // extract the two numbers
		rat = Rational(ratNums[0], ratNums[1]);
	}

	//check if input is equation with two Rationals (solve then give answer)
	if (validationCode == ValidateRationalCode::ABCD_EQUATION){

		strEquation = strInput; // set the equation string

		// the extracted operator
		// find with this regex -{0,1}[1-9]\d{0,4}\/-{0,1}[1-9]\d{0,4}[\+\-\-*\/]
		string regx = "-{0,1}[1-9]\\d{0,4}\\/-{0,1}[1-9]\\d{0,4}[\\+\\-*\\/]";
		smatch match;
		regex_search(strInput, match, regex(regx));
		string temp = match[0];
		theOperator = temp[temp.length() - 1];

		equationEntered = true; // set that there was an equation entered
		getNumbersFromRationalString(strInput, validationCode, ratNums);// extract the four numbers
		// set rat to equal answer of two temp rats
		Rational tempRat1(ratNums[0], ratNums[1]);
		Rational tempRat2(ratNums[2], ratNums[3]);
		switch (theOperator)
		{
		case '+':
			rat = Rational(tempRat1 + tempRat2);
			break;
		case '-':
			rat = Rational(tempRat1 - tempRat2);
			break;
		case '*':
			rat = Rational(tempRat1 * tempRat2);
			break;
		case '/':
			rat = Rational(tempRat1 / tempRat2);
			break;
		default:
			rat = Rational();
			break;
		}
	}

	if (validationCode == ValidateRationalCode::AB_EQUATION){
		strEquation = strInput; // set the equation string

		// the extracted operator
		string regx = "-{0,1}[1-9]\\d{0,4}[\\+\\-*]";
		smatch match;
		regex_search(strInput, match, regex(regx));
		string temp = match[0];
		theOperator = temp[temp.length() - 1];

		equationEntered = true; // set that there was an equation entered
		getNumbersFromRationalString(strInput, validationCode, ratNums);// extract the four numbers
		// set rat to equal answer of two temp rats
		Rational tempRat1(ratNums[0]);
		Rational tempRat2(ratNums[1]);
		switch (theOperator)
		{
		case '+':
			rat = Rational(tempRat1 + tempRat2);
			break;
		case '-':
			rat = Rational(tempRat1 - tempRat2);
			break;
		case '*':
			rat = Rational(tempRat1 * tempRat2);
			break;
		case '/':
			rat = Rational(tempRat1 / tempRat2);
			break;
		default:
			rat = Rational();
			break;
		}
	}

	if (validationCode == ValidateRationalCode::ABC_EQUATION){
		strEquation = strInput; // set the equation string

		// the extracted operator
		// find with this regex -{0,1}[1-9]\d{0,4}\/-{0,1}[1-9]\d{0,4}[\+\-\-*\/]
		string regx = "-{0,1}[1-9]\\d{0,4}\\/-{0,1}[1-9]\\d{0,4}[\\+\\-*\\/]";
		smatch match;
		regex_search(strInput, match, regex(regx));
		string temp = match[0];
		theOperator = temp[temp.length() - 1];

		equationEntered = true; // set that there was an equation entered
		getNumbersFromRationalString(strInput, validationCode, ratNums);// extract the four numbers
		// set rat to equal answer of two temp rats
		Rational tempRat1(ratNums[0], ratNums[1]);
		Rational tempRat2(ratNums[2]);
		switch (theOperator)
		{
		case '+':
			rat = Rational(tempRat1 + tempRat2);
			break;
		case '-':
			rat = Rational(tempRat1 - tempRat2);
			break;
		case '*':
			rat = Rational(tempRat1 * tempRat2);
			break;
		case '/':
			rat = Rational(tempRat1 / tempRat2);
			break;
		default:
			rat = Rational();
			break;
		}
	}

	if (validationCode == ValidateRationalCode::ACD_EQUATION){
		strEquation = strInput; // set the equation string

		// the extracted operator
		string regx = "-{0,1}[1-9]\\d{0,4}[\\+\\-*\\/]";
		smatch match;
		regex_search(strInput, match, regex(regx));
		string temp = match[0];
		theOperator = temp[temp.length() - 1];

		equationEntered = true; // set that there was an equation entered
		getNumbersFromRationalString(strInput, validationCode, ratNums);// extract the four numbers
		// set rat to equal answer of two temp rats
		Rational tempRat1(ratNums[0]);
		Rational tempRat2(ratNums[1], ratNums[2]);
		switch (theOperator)
		{
		case '+':
			rat = Rational(tempRat1 + tempRat2);
			break;
		case '-':
			rat = Rational(tempRat1 - tempRat2);
			break;
		case '*':
			rat = Rational(tempRat1 * tempRat2);
			break;
		case '/':
			rat = Rational(tempRat1 / tempRat2);
			break;
		default:
			rat = Rational();
			break;
		}
	}

	input.setstate(input.goodbit);

	// invalid, set the stream to fail
	if (validationCode == ValidateRationalCode::INVALID){
		input.setstate(input.failbit);
	}

	return input;
}

// friend function from Rational (output)
ostream& operator <<(ostream &output, Rational &rat){
	if (rat.getDenominator() != 0){
		output << rat.getNumerator() << "/" << rat.getDenominator();
	}
	else{
		output << "Invalid";
	}
	return output; // returns an output stream
}

// The main funciton where all the testing goes on for the Rational class.
int main(){
	Rational myRat1;
	Rational myRat2;

	string ans; // stores answer for comparisons
	Rational ratAns; // stores answer for equations

	while (true){
		// ask for Rational Numbers
		cout << "Please select your first Rational.\n";
		do{
			cout << "Enter a '0' for 0/1, put one number for number/1,"
				<< " or input as a rational number (number/number),"
				<< " or input as an equation (number/number(+,-,*,/)number/number):\n";
			cin.clear();
			cin >> myRat1;
		} while (cin.fail());

		cout << endl; // get an extra line in there

		// ask for second number entered if first was not an equation
		if (!equationEntered){
			// ask for Rational Numbers
			cout << "Please select your second Rational.\n";
			do{
				cin.clear();
				cout << "Enter a '0' for 0/1, put one number for number/1,"
					<< " or input as a rational number (number/number),"
					<< " or input as an equation (number/number(+,-,*,/)number/number):\n";
				cin >> myRat2;
			} while (cin.fail());

			cout << endl;

			// check for equality
			cout << myRat1 << " == " << myRat2 << "   ";
			ans = (myRat1 == myRat2) ? "TRUE" : "FALSE";
			cout << ans << endl;

			// check for less than
			cout << myRat1 << " < " << myRat2 << "   ";
			ans = (myRat1 < myRat2) ? "TRUE" : "FALSE";
			cout << ans << endl;

			// check for greater than
			cout << myRat1 << " > " << myRat2 << "   ";
			ans = (myRat1 > myRat2) ? "TRUE" : "FALSE";
			cout << ans << endl;

			// show answer for adding
			cout << myRat1 << " + " << myRat2 << "  = ";
			ratAns = Rational::normalize(myRat1 + myRat2);
			cout << ratAns << endl;

			// show answer for subtracting
			cout << myRat1 << " - " << myRat2 << "  = ";
			ratAns = Rational::normalize(myRat1 - myRat2);
			cout << ratAns << endl;

			// show answer for mulitplying
			cout << myRat1 << " * " << myRat2 << "  = ";
			ratAns = Rational::normalize(myRat1 * myRat2);
			cout << ratAns << endl;

			// show answer for dividing
			cout << myRat1 << " / " << myRat2 << "  = ";
			ratAns = Rational::normalize(myRat1 / myRat2);
			cout << ratAns << endl << endl;

		}
		// equaiton entered;
		else{
			cout << strEquation << "  = ";
			ratAns = Rational::normalize(myRat1); // normalize the answer
			cout << ratAns << endl << endl;// print the answer
		}

		cout << endl << "----------------------------------------------------------\n";
	}

	return 0;
}