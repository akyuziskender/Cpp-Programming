#include "Citizen.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>

Citizen::Citizen(char *idNo, char *name, char *surname, bool hasApp, char *appDate, char *appSlot, char *entryClock) {	// Constructor
	this->idNo = new char[strlen(idNo) + 1];	// allocating memory for the idNo
	strcpy(this->idNo, idNo);

	this->name = new char[strlen(name) + 1];	// allocating memory for the name
	strcpy(this->name, name);

	this->surname = new char[strlen(surname) + 1];	// allocating memory for the surname
	strcpy(this->surname, surname);

	this->hasApp = hasApp;	// assigning the hasApp info

	if (hasApp) {	// if the citizen has an appoinment, then assign his/her appoinment information
		this->appSlot = new char[strlen(appSlot) + 1];
		strcpy(this->appSlot, appSlot);
	}
	else
		appSlot = NULL;	// otherwise it is set to NULL

	char *day, *month, *year, *hour, *min;
	day = strtok(appDate, "-");
	month = strtok(NULL, "-");
	year = strtok(NULL, "-");
	hour = strtok(entryClock, ".");
	min = strtok(NULL, ".");

	appTime = new Time(atoi(day), atoi(month), atoi(year), atoi(hour), atoi(min));

	return;
}

Citizen::~Citizen() {
	// deleting memory
	delete[] idNo;
	delete[] name;
	delete[] surname;
	delete appTime;
	if (hasApp)
		delete[] appSlot;
}

char * Citizen::getName() const {
	return name;	// returning the citizen's name
}

bool Citizen::getCitizensHasAppInfo() const {
	return hasApp;
}

Time * Citizen::getAppTime() const {
	return appTime;	// returning citizen's appTime
}

char * Citizen::getAppSlotInfo() const {
	return appSlot;	// returning citizen's appSlot information
}
