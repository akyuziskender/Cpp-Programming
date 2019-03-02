#pragma once
#include "node_struct.h"

// Stack struct definition
struct Stack {
	Node *head;
	int counter;
	void create();
	void close();
	void push(LicensePlate);
	void pop();
	Node *top();
	bool isempty();
};