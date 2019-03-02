#ifndef CIVILREGISTERY_H
#define CIVILREGISTERY_H
#include "Citizen.h"
#include <list>

class CivilRegistery {
private:
	std::list <Citizen *> wApp;	// queue for the citizens with appoinment
	std::list <Citizen *> wOutApp;	// queue for the citizens without appoinment
public:
	void insertCitizen(Citizen &obj);
	void sortQueues();
	bool removeCitizen(int);
};
#endif