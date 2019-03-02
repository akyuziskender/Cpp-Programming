#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "arrayoperations.h"

using namespace std;

void Array::create() {
	MAX_RECORD = 2;  // Initial max number of person the phonebook can get
	phonebook = new Person_Record[MAX_RECORD];  // allocating memory for phonebook
	number_of_person = 0;  // at first, # of person is 0
}

void Array::add(Person_Record *person) {
	if (number_of_person == MAX_RECORD) {  // in case of reaching max size, increase the phonebook size
		increasing_size();
	}

	(phonebook + number_of_person)->name = new char[strlen(person->name) + 1];  // allocating space for dynamic char array
	strcpy((phonebook + number_of_person)->name, person->name);  // copying the name into the struct
	(phonebook + number_of_person)->surname = new char[strlen(person->surname) + 1];  // allocating space for dynamic char array
	strcpy((phonebook + number_of_person)->surname, person->surname);  // copying the surname into the struct
	(phonebook + number_of_person)->phonenumber = new char[strlen(person->phonenumber) + 1];  // allocating space for dynamic char array
	strcpy((phonebook + number_of_person)->phonenumber, person->phonenumber);  // copying the phonenumber into the struct
	number_of_person++;  // incrementing # of person in the phonebook
	if (number_of_person > 1)  // after adding the person into the last index of array, putting it in its right place by alphabetic order
		alphabetic_order();
}

void Array::remove_person(int person_index) {
	/*
	First, put the person that will be deleted into the last index
	Then, delete the last index from memory
	Decrement # of person by 1
	*/
	int i;
	Person_Record temp;
	for (i = person_index; i < number_of_person - 1; i++) {
		// swap operation
		temp = *(phonebook + i); 
		*(phonebook + i) = *(phonebook + i + 1);
		*(phonebook + i + 1) = temp;
	}
	delete[](phonebook + number_of_person - 1)->name;
	delete[](phonebook + number_of_person - 1)->surname;
	delete[](phonebook + number_of_person - 1)->phonenumber;
	number_of_person--;
}

void Array::list() {
	size_t i;
	cout << endl;
	if (number_of_person == 0) {
		cout << "There is no record.\n" << endl;
		return;
	}
	for (i = 0; i < number_of_person; i++) {
		cout << i + 1 << ". " << (phonebook + i)->name << " " << (phonebook + i)->surname << " " << (phonebook + i)->phonenumber << endl;
	}
}

int Array::search(char name[]) {
	int i, counter = 0;
	char temp1[100], temp2[100];
	cout << endl;
	if (strcmp(name, "*") != 0) {
		for (i = 0; i < number_of_person; i++) {
			strcpy(temp1, name);
			strcpy(temp2, (phonebook + i)->name);
			all_lower(temp1, strlen(temp1));
			all_lower(temp2, strlen(temp2));
			//if (strcmp(name, (phonebook + i)->name) == 0) {
			if (strcmp(temp1, temp2) == 0) {
				cout << i + 1 << ". " << (phonebook + i)->name << " " << (phonebook + i)->surname << " " << (phonebook + i)->phonenumber << endl;
				counter++;
			}
		}
	}
	else {
		list();
		return 1;
	}
	return counter;
}

void Array::update(int person_index) {
	Person_Record new_person;
	char input[100];
	remove_person(person_index);

	cout << "Enter a new name: ";
	cin >> input;
	new_person.name = new char[strlen(input) + 1];
	strcpy(new_person.name, input);
	cout << "Enter a new surname: ";
	cin >> input;
	new_person.surname = new char[strlen(input) + 1];
	strcpy(new_person.surname, input);
	cout << "Enter a new phonenumber: ";
	cin >> input;
	new_person.phonenumber = new char[strlen(input) + 1];
	strcpy(new_person.phonenumber, input);
	add(&new_person);
	delete[] new_person.name;
	delete[] new_person.surname;
	delete[] new_person.phonenumber;
}

void Array::increasing_size() {
	// allocating new space which is larger 2 times than the previous one from memory
	Person_Record *new_phonebook = new Person_Record[MAX_RECORD * 2];
	// copying old datas into the new one
	memcpy(new_phonebook, phonebook, MAX_RECORD * sizeof(Person_Record));

	MAX_RECORD *= 2;  // changing MAX_RECORD value
	delete[] phonebook;  // deleting old array from memory
	phonebook = new_phonebook;
}

void Array::alphabetic_order() {
	Person_Record temp;
	bool swapped = true;
	int index = number_of_person - 1;
	while (swapped) {
		swapped = false;
		if (strcmp((phonebook + index)->name, (phonebook + index - 1)->name) < 0) {
			// swap operation
			temp = *(phonebook + index - 1);
			*(phonebook + index - 1) = *(phonebook + index);
			*(phonebook + index) = temp;
			swapped = true;
		}
		else if (strcmp((phonebook + index)->name, (phonebook + index - 1)->name) == 0) {  // If the names are the same, then sort by surname
			if (strcmp((phonebook + index)->surname, (phonebook + index - 1)->surname) < 0) {
				// swap operation
				temp = *(phonebook + index - 1);
				*(phonebook + index - 1) = *(phonebook + index);
				*(phonebook + index) = temp;
				swapped = true;
			}
		}
		index--;
		if (index == 0) break;
	}
}

// a function that takes a word and converts all its letters to lower case
void Array::all_lower(char *word, int n) {
	int i;  // counter
	for (i = 0; i < n; i++) {
		word[i] = tolower(word[i]);  // converting process
	}
}

void Array::delete_all() {
	// before terminating the program, delete all datas from memory
	int i;
	for (i = 0; i < number_of_person; i++) {
		delete[](phonebook + i)->name;
		delete[](phonebook + i)->surname;
		delete[](phonebook + i)->phonenumber;
	}
	delete[] phonebook;
}
