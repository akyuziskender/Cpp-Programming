#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "arrayoperations.h"

using namespace std;

Array records;

void print_menu();
bool do_operation(char);
void add_new_record();
void delete_record();
void list_records();
void search_record();
void update_record();

int main() {
	records.create();
	char choice;
	bool finish = false;
	do {
		print_menu();
		cin >> choice;
		finish = do_operation(choice);
	} while (finish);
	records.delete_all();
	return 0;
}

void print_menu(){
	//system("cls"); //linux'ta ekran temizleme icin system("clear"); kullaniniz
	system("cls");
	cout << "\nPlease, choose an operation.\n" << endl;
	cout << "\t1. Add a new record" << endl;
	cout << "\t2. Delete a record" << endl;
	cout << "\t3. List all records" << endl;
	cout << "\t4. Search for a record" << endl;
	cout << "\t5. Update a record" << endl;
	cout << "\t6. Exit the application" << endl << endl;
	cout << "Enter an option {1, 2, 3, 4, 5, 6}: ";
}

bool do_operation(char choice) {
	bool flag = true;
	if (choice == '1') add_new_record();
	else if (choice == '2') delete_record();
	else if (choice == '3') list_records();
	else if (choice == '4') search_record();
	else if(choice == '5') update_record();
	else if (choice == '6') flag = false;
	return flag;
}

void add_new_record() {
	Person_Record new_person;
	char input[100];
	cout << "Name: ";
	cin >> input;
	new_person.name = new char[strlen(input) + 1];
	strcpy(new_person.name, input);
	cout << "Surname: ";
	cin >> input;
	new_person.surname = new char[strlen(input) + 1];
	strcpy(new_person.surname, input);
	cout << "Phonenumber: ";
	cin >> input;
	new_person.phonenumber = new char[strlen(input) + 1];
	strcpy(new_person.phonenumber, input);
	records.add(&new_person);
	cout << "Record has been successfully added." << endl;
	delete[] new_person.name;
	delete[] new_person.surname;
	delete[] new_person.phonenumber;
	getchar();
	getchar();
}

void delete_record() {
	int found, index;
	char name[100];
	cout << "Enter the name of the person you want to delete. (Enter * to see the whole list)" << endl;
	cin >> name;
	found = records.search(name);
	if (!found) {
		cout << "No records found." << endl;
	}
	else {
		cout << "Which person do you want to delete? Enter its index." << endl;
		cin >> index;
		records.remove_person(index - 1);
		cout << "Record hes been deleted." << endl;
	}
	getchar();
	getchar();
}

void list_records() {
	records.list();
	getchar();
	getchar();
}

void search_record() {
	char input[100];
	int found;
	cout << "Enter the name you want to search: ";
	cin >> input;
	found = records.search(input);
	if (!found) {
		cout << "No records found." << endl;
	}
	getchar();
	getchar();
}

void update_record() {
	int found, index;
	char input[100];
	cout << "Enter the name of the person you want to update. (Enter * to see the whole list)" << endl;
	cin >> input;
	found = records.search(input);
	if (!found) {
		cout << "No records found." << endl;
	}
	else {
		cout << "Which person do you want to update? Enter its index." << endl;
		cin >> index;
		records.update(index - 1);
		cout << "Record has been successfully updated." << endl;
	}
	getchar();
	getchar();
}
