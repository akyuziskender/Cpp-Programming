#ifndef TIME_H
#define TIME_H
#include <string>

using namespace std;

class Time {
private:
	int day;
	int month;
	int year;
	int hour;
	int minute;
public:
	Time(int, int, int, int, int);	// Constructor
	string getTime() const;
	// Operator overloading
	bool operator < (Time const &obj);
	bool operator > (Time const &obj);
	bool operator == (Time const &obj);
};
#endif