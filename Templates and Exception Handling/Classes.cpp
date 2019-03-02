#include <iostream>
#include "Classes.h"

Money::Money() {	// Default Constructor
	lira = 0;
	kurus = 0;
}

Money::Money(int in_lira, int in_kurus) {
	if (in_lira < 0 || in_kurus < 0)	// if lira or kurus is less than zero
		throw "The amount of money cannot be below zero!";	// throw an exception
	else {
		lira = in_lira;
		kurus = in_kurus;
	}
}

bool Money::operator<(int in_lira) {	// < operator with an integer
	if (this->lira < in_lira)
		return true;
	else
		return false;
}

bool Money::operator>(int in_lira) {	// > operator with an integer
	if (this->lira > in_lira)
		return true;
	else if (this->lira == in_lira && this->kurus > 0)
		return true;
	else
		return false;
}

Money & Money::operator=(Money const & obj) {	// assign operator
	this->lira = obj.lira;
	this->kurus = obj.kurus;
	return *this;
}

Money & Money::operator=(int in_lira) {	// assign operator. It assigns only lira. Kurus is assigned to 0 by default.
	this->lira = in_lira;
	this->kurus = 0;
	return *this;
}

Money & Money::operator+=(Money const & obj) {	// += operator
	this->lira += obj.lira;
	this->kurus += obj.kurus;
	if (this->kurus >= 100) {
		this->lira += this->kurus / 100;
		this->kurus = kurus % 100;
	}
	return *this;
}

Money & Money::operator-=(Money const & obj) {	// -= operator
	this->lira -= obj.lira;
	this->kurus -= obj.kurus;
	if (this->kurus < 0) {
		this->lira--;
		this->kurus += 100;
	}
	return *this;
}

ostream & operator<<(ostream &out, const Money &obj) {
	out << obj.lira << " lira : " << obj.kurus << " kurus";
	return out;
}
