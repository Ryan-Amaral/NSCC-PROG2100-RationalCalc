// Implementation class for Rational

#include <iostream>
#include <sstream>
#include "Rational.h"
using namespace std;

// default constructor, 0 for numerator, 1 for denominator
Rational::Rational(void)
		: numerator(0), denominator(1), valid(true){}

// constructor to fill in only numerator, denomintor is 1
Rational::Rational(int wholeNumber)
		: numerator(wholeNumber), denominator(1), valid(true){}

// constructor to fill in numerator and denominator
Rational::Rational(int num, int den)
		: numerator(num), denominator(den), valid(den != 0){
}

// getters and setters

int Rational::getNumerator(){
	return this->numerator;
}

void Rational::setNumerator(int numerator){
	this->numerator = numerator;
}

int Rational::getDenominator(){
	return this->denominator;
	this->setValid(this->denominator != 0);
}

void Rational::setDenominator(int denominator){
	this->denominator = denominator;
}

bool Rational::getValid(){
	return this->valid;
}

void Rational::setValid(bool valid){
	this->valid = valid;
}

// plus overload
Rational Rational::operator +(Rational rat){
	Rational tempRat = rat; // temp rational for equation because swapping involved

	// get same denominator by multiplying numerator and denominator on both sides by the other denominator
	rat.setNumerator(this->getDenominator() * rat.getNumerator());
	rat.setDenominator(this->getDenominator() * rat.getDenominator());
	tempRat.setNumerator(tempRat.getDenominator() * this->getNumerator()); // use tempRat for original values of rat
	// don't need to set other denominator because they are both the same so we can use the other's

	// denominators are now equivalent with proportional numerators, numerators can be added
	rat.setNumerator(tempRat.getNumerator() + rat.getNumerator());
	
	return rat;
}

// minus overload
Rational Rational::operator -(Rational rat){
	Rational tempRat = rat; // temp rational for equation because swapping involved

	// get same denominator by multiplying numerator and denominator on both sides by the other denominator
	rat.setNumerator(this->getDenominator() * rat.getNumerator());
	rat.setDenominator(this->getDenominator() * rat.getDenominator());
	tempRat.setNumerator(tempRat.getDenominator() * this->getNumerator()); // use tempRat for original values of rat
	// don't need to set other denominator because they are both the same so we can use the other's

	// denominators are now equivalent with proportional numerators, numerators can be subtracted
	rat.setNumerator(tempRat.getNumerator() - rat.getNumerator());

	return rat;
}

// multiply overload
Rational Rational::operator *(Rational rat){
	// multiply numerator by numerator and denominator by denominator
	rat.setNumerator(this->getNumerator() * rat.getNumerator());
	rat.setDenominator(this->getDenominator() * rat.getDenominator());

	return rat;
}

// divide overload
Rational Rational::operator /(Rational rat){
	if (rat.getValid()){
		Rational tempRat = rat;
		// multiply numerator 1 by denominator 2 and denominator 1 by numerator 2
		rat.setNumerator(this->getNumerator() * tempRat.getDenominator());
		rat.setDenominator(this->getDenominator() * tempRat.getNumerator());
	}
	else{
		rat.setDenominator(0);
	}

	return rat;
}

// greater than overload
bool Rational::operator >(Rational &rat){
	if (this->getDenominator() != 0 && rat.getDenominator() != 0){
		// cast fractions as floats and compare
		float lRat = (float)this->getNumerator() / (float)this->getDenominator();
		float rRat = (float)rat.getNumerator() / (float)rat.getDenominator();

		return (lRat > rRat) ? true : false;
	}
	else{
		return false;
	}
}

// lesser than overload
bool Rational::operator <(Rational &rat){
	if (this->getDenominator() != 0 && rat.getDenominator() != 0){
		// cast fractions as floats and compare
		float lRat = (float)this->getNumerator() / (float)this->getDenominator();
		float rRat = (float)rat.getNumerator() / (float)rat.getDenominator();

		return (lRat < rRat) ? true : false;
	}
	else{
		return false;
	}
}

// assignment overload
Rational Rational::operator =(Rational &rat){
	this->numerator = rat.numerator;
	this->denominator = rat.denominator;
	// check if denominator is valid (0 = not valid)
	this->setValid(this->denominator != 0);

	return *this;
}

// equality overload
bool Rational::operator ==(Rational &rat){
	if (this->getDenominator() != 0 && rat.getDenominator() != 0){
		// cast fractions as floats and compare
		float lRat = (float)this->getNumerator() / (float)this->getDenominator();
		float rRat = (float)rat.getNumerator() / (float)rat.getDenominator();

		return (lRat == rRat) ? true : false;
	}
	else{
		return false;
	}
}

// greater equal overload
bool Rational::operator >=(Rational &rat){
	if (this->getDenominator() != 0 && rat.getDenominator() != 0){
		// cast fractions as floats and compare
		float lRat = (float)this->getNumerator() / (float)this->getDenominator();
		float rRat = (float)rat.getNumerator() / (float)rat.getDenominator();

		return (lRat >= rRat) ? true : false;
	}
	else{
		return false;
	}
}

// less equal overload
bool Rational::operator <=(Rational &rat){
	if (this->getDenominator() != 0 && rat.getDenominator() != 0){
		// cast fractions as floats and compare
		float lRat = (float)this->getNumerator() / (float)this->getDenominator();
		float rRat = (float)rat.getNumerator() / (float)rat.getDenominator();

		return (lRat <= rRat) ? true : false;
	}
	else{
		return false;
	}
}

// not equal overload
bool Rational::operator !=(Rational &rat){
	if (this->getDenominator() != 0 && rat.getDenominator() != 0){
		// cast fractions as floats and compare
		float lRat = (float)this->getNumerator() / (float)this->getDenominator();
		float rRat = (float)rat.getNumerator() / (float)rat.getDenominator();

		return (lRat != rRat) ? true : false;
	}
	else{
		return false;
	}
}

// friend overloads to be implemented else-where (I/O)

// convert to string
string Rational::toString(){
	stringstream strStream;
	string num, den; // stores values as strings
	string result;

	if (this->getDenominator() != 0){
		strStream << this->getNumerator();
		strStream >> num;
		strStream.clear();

		strStream << this->getDenominator();
		strStream >> den;
		strStream.clear();

		result = num + "/" + den;
	}
	else{
		result = "Invalid";
	}
	
	return result;
}

// reduce the fraction
Rational Rational::normalize(Rational rat){
	// reduce the fraction, utilizing Euclids algorithm
	int bigNum;
	int smallNum;
	int remainder = -1;
	int gcd; // greatest common denominator for numerator and denominator

	// get the bigger number, and smaller number of numerator and denominator
	if (rat.getNumerator() > rat.getDenominator()){
		bigNum = rat.getNumerator();
		smallNum = rat.getDenominator();
	}
	else{
		bigNum = rat.getDenominator();
		smallNum = rat.getNumerator();
	}

	if (!(smallNum == 0 || bigNum == 0)){

		// if bigNum/smallNum has remainder, neither is gcd. else small num is gcd
		while (remainder != 0){
			remainder = bigNum % smallNum;
			if (remainder != 0){
				bigNum = smallNum;
				smallNum = remainder;
			}
		}
		gcd = smallNum;

		rat.setNumerator(rat.getNumerator() / gcd);
		rat.setDenominator(rat.getDenominator() / gcd);

		rat = properSign(rat); // set the signs to be proper

	}
	else if (rat.getNumerator() == 0 && rat.getDenominator() != 0){
		rat.setDenominator(1);
	}
	

	return rat;
}

Rational Rational::properSign(Rational rat){
	// if fraction >= 0, have no negative signs
	if (((float)rat.getNumerator() / (float)rat.getDenominator()) >= 0){
		rat.setNumerator(abs(rat.getNumerator()));
		rat.setDenominator(abs(rat.getDenominator()));
	}
	// else put negative sign on only numerator
	else{
		if (rat.getNumerator() > 0){
			rat.setNumerator(rat.getNumerator() * -1);
		}
		rat.setDenominator(abs(rat.getDenominator())); // denominator is always positive
	}

	return rat;
}