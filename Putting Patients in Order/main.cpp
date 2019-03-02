/* @Author  
 * Student Name: İskender Akyüz 
 * Student ID : 150150150
 * Date: 10.12.2017  
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "queue_struct.h"

using namespace std;

Queue RedPatients, YellowPatients, GreenPatients;	// queues in the hospital
Queue Patients;	// a queue for the all patients
int prog_time;	// a global variable for the time in the program
// function prototypes
void Initialization();
void Close();
void ReadFile();
void TakePatientToQueues();
void TreatThePatients();

int main() {
	Initialization();
	ReadFile();	// reading the file
	TreatThePatients();	// healing patients
	Close();	// closing the program
	return 0;
}

void Initialization() {
	// cretae the queues
	RedPatients.create();	// a queue for the patients with compleint RED
	YellowPatients.create();	// a queue for the patients with compleint YELLOW
	GreenPatients.create();	// a queue for the patients with compleint GREEN
	Patients.create();	// cretae the queue
	prog_time = 0;	// set the time 0
	return;
}

void Close() {
	// close the queues
	RedPatients.close();
	YellowPatients.close();
	GreenPatients.close();
	Patients.close();
	return;
}

void ReadFile() {
	ifstream patientsFile("patientsInfo.txt");	// opening the file for reading
	string line;
	Patient newperson;	// a temp struct
	int counter = 1;

	while (getline(patientsFile, line)) {	// reading the file line by line
		istringstream ss(line);	// splitting the string that we took from the file
		char patient_num[20];	// a char array to hold the patients' number
		int arrivingTime, treatmentTime;	// local variables
		char compleint[10];	// a char array to hold the patients' compleint

		ss >> patient_num >> arrivingTime >> treatmentTime >> compleint;
		if (strncmp(patient_num, "Patient", 7) == 0) {	// this if statement prevent to take the first line in the file
			newperson.patient_number = counter;	// assigning his/her number to the patient
			newperson.arriving_time = arrivingTime;	// assigning his/her arriving time
			newperson.treatment_time = treatmentTime;	// assigning his/her treatment time
			// assigning his/her compleint type
			if (strcmp(compleint, "RED") == 0)
				newperson.compleint = RED;
			else if (strcmp(compleint, "YELLOW") == 0)
				newperson.compleint = YELLOW;
			else if (strcmp(compleint, "GREEN") == 0)
				newperson.compleint = GREEN;
			Patients.enqueue(&newperson);	// adding his/her into the queue
			counter++;	// increment the counter
		}
	}
	return;
}

void TakePatientToQueues() {
	// what this function does is that when the time (arriving time) comes for the patients, it takes them into queues (R, Y, G)
	if (!Patients.isempty()) {
		Patient *patient;
		patient = Patients.first();	// first person in the queue
		if (prog_time >= patient->arriving_time) {	// if the time mathces with the patient's arriving time
			if (patient->compleint == RED)	// if his/her compleint is Red, add the patient to the RED queue
				RedPatients.enqueue(patient);
			else if (patient->compleint == YELLOW)	// if his/her compleint is Yellow, add the patient to the YELLOW queue
				YellowPatients.enqueue(patient);
			else if (patient->compleint == GREEN)	// if his/her compleint is Green, add the patient to the GREEN queue
				GreenPatients.enqueue(patient);
			Patients.dequeue();
		}
	}
	return;
}

void TreatThePatients() {
	Patient *patient;
	size_t i;
	while (!Patients.isempty() || !RedPatients.isempty() || !YellowPatients.isempty() || !GreenPatients.isempty()) {	// while none of the queues is empty

		if(RedPatients.isempty() && YellowPatients.isempty() && GreenPatients.isempty())
			TakePatientToQueues();	// taking patients into the queues

		if (!RedPatients.isempty()) {
			patient = RedPatients.first();
			patient->compleint = YELLOW;	// since we are healing the patient, his/her compleint will be YELLOW
			patient->treatment_time--;	// decrement the treatment time
			prog_time += 1;	// time passes, so increment the prog_time
			TakePatientToQueues();	// taking patients into the queues
			cout << prog_time << ".time slice Patient" << patient->patient_number << endl;
			if (patient->treatment_time > 0)	// after RED treatment, if the patients is still sick, then send him/her to the YELLOW queue
				YellowPatients.enqueue(patient);
			RedPatients.dequeue();	// delete the patient from RED queue
		}
		else if (!YellowPatients.isempty()) {
			patient = YellowPatients.first();
			patient->compleint = GREEN;	// since we are healing the patient, his/her compleint will be GREEN
			for (i = 0; i < 2; i++) {	// duration of treatment for YELLOW is 2
				patient->treatment_time--;	// decrement the treatment time
				prog_time++;	// time passes, so increment the prog_time
				TakePatientToQueues();	// taking patients into the queues
				cout << prog_time << ".time slice Patient" << patient->patient_number << endl;
				if (patient->treatment_time <= 0)	// if the patient become well, then break the loop
					break;
			}
			if (patient->treatment_time > 0)	// after YELLOW treatment, if the patients is still sick, then send him/her to the GREEN queue
				GreenPatients.enqueue(patient);
			YellowPatients.dequeue();	// delete the patient from YELLOW queue
		}
		else if (!GreenPatients.isempty()) {
			patient = GreenPatients.first();
			for (i = 0; i < 3; i++) {	// duration of treatment for YELLOW is 3
				patient->treatment_time--;
				prog_time++;	// time passes, so increment the prog_time
				TakePatientToQueues();	// taking patients into the queues
				cout << prog_time << ".time slice Patient" << patient->patient_number << endl;
				if (patient->treatment_time <= 0)	// if the patient become well, then break the loop
					break;
			}
			if (patient->treatment_time > 0)	// after GREEN treatment, if the patients is still sick, then send him/her to the GREEN queue again
				GreenPatients.enqueue(patient);	// add the patient to the end of the queueu
			GreenPatients.dequeue();	// taking the patient from the first
		}
		else {
			prog_time++;	// time passes, so increment the prog_time
			cout << prog_time << ".time slice No treatment" << endl;
		}
	}
}

// by marnop