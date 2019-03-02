#include <iostream>
#include "Classes.h"

using namespace std;

int main() {
	try {
		genericArray<int> m1(5);	// a generic array with integer numbers
		genericArray<double> m2(5);	// a generic array with double numbers
		genericArray<Money> m3(5);	// a generic array with Money objects

		//Money d(-1, 89);
		Money a(10, 5);
		Money b(10, 5);
		Money c(43, 7);
		Money k(50, 6);
		Money m(10, 20);
		Money bonus(5, 0);	// bonus money for the prize

		m3.elements[0] = a;
		m3.elements[1] = b;
		m3.elements[2] = c;
		m3.elements[3] = k;
		m3.elements[4] = m;

		m2.elements[0] = 12.5;
		m2.elements[1] = 11.6;
		m2.elements[2] = 13.9;
		m2.elements[3] = 23.7;
		m2.elements[4] = 130.7;

		m1.elements[0] = 1;
		m1.elements[1] = 2;
		m1.elements[2] = 5;
		m1.elements[3] = 9;
		m1.elements[4] = 90;

		m3.total = m3.sum();	// calculating the sum
		cout << "Your total amount for money objects array is " << m3.total << endl;
		if (m3.total > 100) {	// if it is greater than 100, add a bonus to it
			m3.total += bonus;
			cout << "You have won 5 tl bonus, your new amount is " <<  m3.total << endl << endl;
		}
		else if (m3.total < 100) {	// if it is less than 100, take a bonus from it
			m3.total -= bonus;
			cout << "You have lost 5 tl, your new amount is " << m3.total << endl << endl;
		}

		m2.total = m2.sum();	// calculating the sum
		cout << "The total of double array is " << m2.total << endl;
		if (m2.total > 100.0) {	// if it is greater than 100, add a bonus to it
			m2.total += 5.0;
			cout << "You have won 5 tl bonus, your new amount is " << m2.total << endl << endl;
		}
		else if (m3.total < 100.0) {	// if it is less than 100, take a bonus from it
			m2.total -= 5.0;
			cout << "You have lost 5 tl, your new amount is " << m2.total << endl << endl;
		}

		m1.total = m1.sum();	// calculating the sum
		cout << "The total of integer array is " << m1.total << endl;
		if (m1.total > 100) {	// if it is greater than 100, add a bonus to it
			m1.total += 5;
			cout << "You have won 5 tl bonus, your new amount is " << m1.total << endl << endl;
		}
		else if (m1.total < 100) {	// if it is less than 100, take a bonus from it
			m1.total -= 5;
			cout << "You have lost 5 tl, your new amount is " << m1.total << endl << endl;
		}
	}
	catch (const char * msg) {	// exception handler
		cout << msg << endl;
	}

	return 0;
}