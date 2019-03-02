#include "Time.h"
#include <string.h>
#include <sstream>  // for string streams
#include <string>  // for string

Time::Time(int in_day, int in_month, int in_year, int in_hour, int in_minute) : day(in_day), month(in_month), year(in_year), hour(in_hour), minute(in_minute) {};	// Constructor

string Time::getTime() const {
	ostringstream hour_, minute_, day_, month_, year_;
	hour_ << hour;
	minute_ << minute;
	day_ << day;
	month_ << month;
	year_ << year;
	return (hour < 10 ? "0" + hour_.str() : hour_.str()) + "." + (minute < 10 ? "0" + minute_.str() : minute_.str()) + " "
		+ (day < 10 ? "0" + day_.str() : day_.str()) + "/" + (month < 10 ? "0" + month_.str() : month_.str()) + "/" + year_.str();
}

bool Time::operator<(Time const & obj) {
	if (year < obj.year)	// first check the year
		return true;
	else if (year == obj.year && month < obj.month)	// then check both year and month
		return true;
	else if (year == obj.year && month == obj.month && day < obj.day)	// then check year, month and day
		return true;
	else if (year == obj.year && month == obj.month && day == obj.day && hour < obj.hour)	// then check year, month, day, and hour
		return true;
	else if (year == obj.year && month == obj.month && day == obj.day && hour == obj.hour && minute < obj.minute)	// then check all of them
		return true;
	else
		return false;
}

bool Time::operator>(Time const & obj) {
	if (year > obj.year)	// first check the year
		return true;
	else if (year == obj.year && month > obj.month)	// then check both year and month
		return true;
	else if (year == obj.year && month == obj.month && day > obj.day)	// then check year, month and day
		return true;
	else if (year == obj.year && month == obj.month && day == obj.day && hour > obj.hour)	// then check year, month, day, and hour
		return true;
	else if (year == obj.year && month == obj.month && day == obj.day && hour == obj.hour && minute > obj.minute)	// then check all of them
		return true;
	else
		return false;
}

bool Time::operator==(Time const & obj) {
	return (day == obj.day && month == obj.month && year == obj.year);	// compare only date
}
