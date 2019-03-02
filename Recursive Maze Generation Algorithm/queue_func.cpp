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
	Node *p;
	while (front) {
		p = front;
		front = front->next;
		delete[] p->data;
		delete p;
	}
}

void Queue::enqueue(LicensePlate newdata) {
	Node *newnode = new Node;
	newnode->data = new char[strlen(newdata) + 1];
	newnode->data[strlen(newnode->data)] = '\0';
	strcpy(newnode->data, newdata);
	newnode->next = NULL;
	if (isempty()) {
		back = newnode;
		front = back;
	}
	else {
		back->next = newnode;
		back = newnode;
	}
}

LicensePlate Queue::dequeue() {
	Node *topnode;
	LicensePlate temp;
	topnode = front;
	front = front->next;
	temp = topnode->data;
	//delete topnode->data;
	delete topnode;
	return temp;
}

bool Queue::isempty() {
	return front == NULL;
}