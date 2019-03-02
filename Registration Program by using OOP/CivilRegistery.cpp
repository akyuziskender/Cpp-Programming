#include "CivilRegistery.h"
#include <sstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>

// compare function for citizens without appoinment
bool compare_time_wOutApp(const Citizen * first, const Citizen * second) {
	Time *first_time = (*first).getAppTime();	// getting appoinment information of the first citizen
	Time *second_time = (*second).getAppTime();	// getting appoinment information of the second citizen

	if (*first_time < *second_time)	// if the first citizen should be served before the second one, return true
		return true;
	else
		return false;
}

// compare function for citizens with appoinment
bool compare_time_wApp(const Citizen * first, const Citizen * second) {
	bool less = false;
	Time *first_time = (*first).getAppTime();	// getting appoinment information of the first citizen
	Time *second_time = (*second).getAppTime();	// getting appoinment information of the second citizen

	char *first_appSlot = new char[strlen((*first).getAppSlotInfo()) + 1];	// allocating memory
	strcpy(first_appSlot, (*first).getAppSlotInfo());
	char *second_appSlot = new char[strlen((*second).getAppSlotInfo()) + 1];	// allocating memory
	strcpy(second_appSlot, (*second).getAppSlotInfo());

	if (*first_time == *second_time) {
		char *f_hour = strtok(first_appSlot, "-");	// spliting the string
		char *s_hour = strtok(second_appSlot, "-");	// spliting the string
		char *f_h, *f_m, *s_h, *s_m;
		f_h = strtok(f_hour, ".");	// spliting the string to get hour info from appSlot for the first citizen
		f_m = strtok(NULL, ".");	// spliting the string to get minute info from appSlot for the first citizen
		s_h = strtok(s_hour, ".");	// spliting the string to get hour info from appslot for the second citizen
		s_m = strtok(NULL, ".");	// spliting the string to get minute info from appSlot for the second citizen

		if (atoi(f_h) < atoi(s_h)) {	// if their app dates are the same, then check their appoinment hours
			less = true;
		}
		else if (atoi(f_h) == atoi(s_h)) {	// if their appoinment hours are the same, then check their appoinment minutes
			if (atoi(f_m) < atoi(s_m))
				less = true;
			else if (atoi(f_m) == atoi(s_m)) {
				if (*first_time < *second_time)	// since their appoinment hours and minutes are the same, then check their entryClock's by comparing their appTime
					less = true;
			}
		}
	}
	else if (*first_time < *second_time)	// checking their appTime, if the first one's is less, then he/she should be served first
		less = true;
	else
		less = false;


	delete[] first_appSlot;	// delete memory
	delete[] second_appSlot;	// delete memory
	return less;
}

void CivilRegistery::insertCitizen(Citizen & obj) {
	if (obj.getCitizensHasAppInfo())
		wApp.push_back(&obj);	// add the citizen into queue
	else
		wOutApp.push_back(&obj);	// add the citizen into queue
}
void CivilRegistery::sortQueues() {
	wApp.sort(compare_time_wApp);	// after adding citizen into queue, sort the queue
	wOutApp.sort(compare_time_wOutApp);	// after adding citizen into queue, sort the queue
}
// function that removes the citizens and returns if the queue is empty
bool CivilRegistery::removeCitizen(int list_no) {
	if (list_no == 0 && !wApp.empty()) {
		cout << (*wApp.front()).getName() << endl;	// print the citizen's name who was served by officers
		Citizen *temp = wApp.front();
		wApp.pop_front();
		delete temp;
		return false;
	}
	else if (list_no == 1 && !wOutApp.empty()) {
		cout << (*wOutApp.front()).getName() << endl;	// print the citizen's name who was served by officers
		Citizen *temp = wOutApp.front();
		wOutApp.pop_front();
		delete temp;
		return false;
	}
	return true;
}
