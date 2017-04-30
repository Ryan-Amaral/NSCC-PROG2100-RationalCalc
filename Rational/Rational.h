// Rational header file

#pragma once

#define RATIONAL_H
	
#include <iostream>
using namespace std;

class Rational{
private:
	int numerator;
	int denominator;
	bool valid = true;
public:
	// constructors
	Rational(void); // set rational to 0/1
	Rational(int); // set rational to int/1
	Rational(int, int); // set rational to int1/int2

	// accessors and mutators
	int getNumerator();
	void setNumerator(int);
	int getDenominator();
	void setDenominator(int);
	bool getValid();
	void setValid(bool);

	// operator overloads
	Rational operator +(Rational rat);
	Rational operator -(Rational rat);
	Rational operator *(Rational rat);
	Rational operator /(Rational rat);
	bool operator >(Rational &rat);
	bool operator <(Rational &rat);
	Rational operator =(Rational &rat);
	bool operator ==(Rational &rat);
	bool operator >=(Rational &rat);
	bool operator <=(Rational &rat);
	bool operator !=(Rational &rat);

	// io overloads
	friend istream& operator >>(istream &input, const Rational &rat);
	friend ostream& operator <<(ostream &output, const Rational &rat);

	string toString();

	// reduce to smallest denominator
	static Rational normalize(Rational);

	// set the negative signs right (only in numerator or not at all)
	static Rational properSign(Rational);
};