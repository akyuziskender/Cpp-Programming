#pragma once
#include "node_struct.h"

// Queue struct definition
struct Queue {
	Node *front;
	Node *back;
	void create();
	void close();
	void enqueue(LicensePlate);
	LicensePlate dequeue();
	bool isempty();
};