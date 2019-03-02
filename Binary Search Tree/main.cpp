#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "struct.h"

using namespace std;

tree phonebook;

void print_menu();
bool do_operation(char);
void add_new_person();
void delete_person();
void update_person();
void search_record();
void list_records();

int main() {
	phonebook.create();
	char choice;
	bool finish = false;
	do {
		print_menu();
		cin >> choice;
		finish = do_operation(choice);
	} while (finish);
	phonebook.close();
	return 0;
}

void print_menu() {
	//system("cls"); //linux'ta ekran temizleme icin system("clear"); kullaniniz
	system("cls");
	cout << "\n>> Please, choose an operation.\n" << endl;
	cout << "\t1. Add a new person" << endl;
	cout << "\t2. Delete a person" << endl;
	cout << "\t3. Update a person" << endl;
	cout << "\t4. Search for a record" << endl;
	cout << "\t5. List all records" << endl;
	cout << "\t6. Exit the application" << endl << endl;
	cout << ">> Enter an option {1, 2, 3, 4, 5, 6}: ";
}

bool do_operation(char choice) {
	bool flag = true;
	if (choice == '1') add_new_person();
	else if (choice == '2') delete_person();
	else if (choice == '3') update_person();
	else if (choice == '4') search_record();
	else if (choice == '5') list_records();
	else if (choice == '6') flag = false;
	return flag;
}

void add_new_person() {
	char name[100], number[100];
	cout << "\n>> Name: ";
	cin >> name;
	cout << ">> Phone number: ";
	cin >> number;
	phonebook.add(name, number);
	getchar();
	getchar();
}

void delete_person() {
	char name[100];
	cout << "\n>> Please, enter the name of person you want to delete: ";
	cin >> name;
	if (phonebook.remove(name, '+'))
		cout << ">> The person has been deleted." << endl;
	else
		cout << ">> Could not find record to remove." << endl;
	getchar();
	getchar();
}

void update_person() {
	char name[100], new_name[100];
	cout << "\n>> Enter the name of person you want to update: ";
	cin >> name;
	cout << ">> Enter a new name: ";
	cin >> new_name;
	if (phonebook.update(name, new_name))
		cout << ">> The person has been updated." << endl;
	else
		cout << ">> Could not find record to update." << endl;
	getchar();
	getchar();
}

void list_records() {
	cout << endl;
	phonebook.print_inorder(phonebook.root);
	getchar();
	getchar();
}

void search_record() {
	char name[30];
	Phone_node *found;
	number *num;
	cout << ">> Who do you want to search? ";
	cin >> name;
	found = phonebook.search(name);
	if (found == 0) cout << ">> No records found." << endl;
	else {
		cout << "\n>> " << found->name << endl;
		num = found->phonenum;
		while (num) {
			cout << "\t" << num->phonenum << endl;
			num = num->next;
		}
	}
	getchar();
	getchar();
}