#include <iostream>
#include <string.h>
#include "queue_struct.h"

// create empty queue
void Queue::create() {
	front = NULL;
	back = NULL;
}

// close the queue
void Queue::close() {
	Patient *p;
	while (front) {
		p = front;
		front = front->next;
		delete p;	// deleting memory
	}
}

void Queue::enqueue(Patient *newperson) {
	Patient *newpatient = new Patient;	// allocating new space from memory
	newpatient->patient_number = newperson->patient_number;	// copying the patient number
	newpatient->arriving_time = newperson->arriving_time;	// copying arriving time
	newpatient->treatment_time = newperson->treatment_time;	// copying treatment time
	newpatient->compleint = newperson->compleint;	// copying compleint
	newpatient->next = NULL;	// make its next NULL
	if (isempty()) {	// if it is empty, add to front
		back = newpatient;
		front = back;
	}
	else {	// otherwise, add to the back
		back->next = newpatient;
		back = newpatient;
	}
}

void Queue::dequeue() {
	Patient *topnode;
	topnode = front;
	front = front->next;	// the second will be the first
	delete topnode;	// deleting memory
	return;
}

Patient *Queue::first() {
	return front;
}

bool Queue::isempty() {
	return front == NULL;
}