#ifndef CITIZEN_H
#define CITIZEN_H
#include "Time.h"
#include <string>

class Citizen {
private:
	char *idNo;
	char *name;
	char *surname;
	bool hasApp;
	Time *appTime;
	char *appSlot;
public:
	Citizen(char *, char *, char*, bool, char *, char *, char *);	// Constructor
	~Citizen();
	char * getName() const;
	bool getCitizensHasAppInfo() const;
	Time * getAppTime() const;
	char * getAppSlotInfo() const;
};
#endif