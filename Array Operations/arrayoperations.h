#ifndef ARRAYOPERATIONS_H
#define ARRAYOPERATIONS_H
#include <stdio.h>
#include "record.h"

typedef struct {
	Person_Record *phonebook;
	int MAX_RECORD;
	int number_of_person;

	void create();
	void add(Person_Record *);
	void remove_person(int person_index);
	void list();
	int search(char name[]);
	void update(int person_index);
	void increasing_size();
	void alphabetic_order();
	void all_lower(char *, int);
	void delete_all();
}Array;
#endif
