 #include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "CivilRegistery.h"

using namespace std;

CivilRegistery civilRegistery;

void ReadFile();
void ServeTheCitizens();

int main() {
	ReadFile();	// putting citizens into queues
	ServeTheCitizens();	// serving them in order
	return 0;
}

void ReadFile() {
	ifstream patientsFile("input.txt");	// opening the file for reading
	string line;
	bool first_line = true;
	while (getline(patientsFile, line)) {	// reading the file line by line
		istringstream ss(line);
		if (first_line) {	// skip the first line in input file
			first_line = false;
			continue;
		}
		char citizenID[4], citizenName[20], citizenSurname[20], citizenHasApp[6], citizenAppDate[10], citizenAppSlot[12], citizenEntry[6];

		ss >> citizenID >> citizenName >> citizenSurname >> citizenHasApp >> citizenAppDate >> citizenAppSlot >> citizenEntry;	// split the line that we will get from the input file
		Citizen *newperson = new Citizen(citizenID, citizenName, citizenSurname, strcmp(citizenHasApp, "TRUE") == 0, citizenAppDate, citizenAppSlot, citizenEntry);
		civilRegistery.insertCitizen(*newperson); // insert the citizen into one of the queues in the civil registery class
	}
	civilRegistery.sortQueues();	// after adding all citizens into lists, sort the list according to their entryClock and appTime
	return;
}

void ServeTheCitizens() {
	bool finished = false;
	cout << "Citizens with an appointment :" << endl;
	do {
		finished = civilRegistery.removeCitizen(0);	// 0 is for the ones with an appoinment
	} while (!finished);
	cout << "\nCitizens without an appointment :" << endl;
	do {
		finished = civilRegistery.removeCitizen(1);	// 1 is for the ones without an appoinment
	} while (!finished);
}
