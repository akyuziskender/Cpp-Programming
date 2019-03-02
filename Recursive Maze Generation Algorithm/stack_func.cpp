#include <iostream> // allows program to perform input and output
#include <string.h> // program uses C++ standard string class
#include "stack_struct.h" // include implementation of struct Stack

// create empty stack
void Stack::create() {
	head = NULL;
	counter = 0;
}

// close the stack
void Stack::close() {
	Node *p;
	while (head) {
		p = top();
		head = head->next;
		delete[] p->data;
		delete p;
	}
}

// push new element onto stack
void Stack::push(LicensePlate newdata) {
	Node *newnode = new Node;
	newnode->data = new char[strlen(newdata) + 1];
	newnode->data[strlen(newnode->data)] = '\0';
	strcpy(newnode->data, newdata);
	newnode->next = head;
	head = newnode;
	counter++;
}

// pop an element from stack
void Stack::pop() {
	Node *topnode;
	char temp[50];
	topnode = head;
	head = head->next;
	strcpy(temp, topnode->data);
	delete[] topnode->data;
	delete topnode;
	counter--;
}

Node *Stack::top() {
	return head;
}

// check if stack is empty
bool Stack::isempty() {
	return head == NULL;
}