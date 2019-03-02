#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "listoperations.h"

using namespace std;

List phonebook;

void print_menu();
bool do_operation(char);
void add_new_person();
void add_new_number();
void delete_person();
void delete_number();
void update_person();
void update_number();
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

void print_menu(){
	//system("cls"); //linux'ta ekran temizleme icin system("clear"); kullaniniz
	system("clear");
	cout << "\nPlease, choose an operation.\n" << endl;
	cout << "\t1. Add a new person" << endl;
    cout << "\t2. Add a new number" << endl;
	cout << "\t3. Delete a person" << endl;
    cout << "\t4. Delete a number" << endl;
    cout << "\t5. Update a person" << endl;
    cout << "\t6. Update a number" << endl;
	cout << "\t7. Search for a record" << endl;
    cout << "\t8. List all records" << endl;
	cout << "\t9. Exit the application" << endl << endl;
	cout << "Enter an option {1, 2, 3, 4, 5, 6, 7, 8, 9}: ";
}

bool do_operation(char choice) {
	bool flag = true;
	if (choice == '1') add_new_person();
    else if (choice == '2') add_new_number();
	else if (choice == '3') delete_person();
    else if (choice == '4') delete_number();
    else if (choice == '5') update_person();
    else if (choice == '6') update_number();
    else if (choice == '7') search_record();
	else if (choice == '8') list_records();
	else if (choice == '9') flag = false;
	return flag;
}

void add_new_person() {
	char name[100];
	cout << "Name: ";
    cin >> name;
	if(phonebook.addPerson(name)) {
        cout << "The record has been successfully added." << endl;
    }
    else{
        cout << "There is already a record in this name." << endl;
    }
	getchar();
	getchar();
}

void add_new_number() {
	char name[30], num[15], type[7];
    bool found;
	cout << "Enter a name: ";
    cin >> name;
    cout << "Enter its type: ";
    cin >> type;
    cout << "Enter its phonenumber: ";
    cin >> num;
	found = phonebook.addNumber(name, num, type);
	if(found) cout << "The number has been successfully added to the person." << endl;
	getchar();
	getchar();
}

void delete_person() {
	char name[30];
	cout << "Enter the name you want to delete: ";
    cin >> name;
	phonebook.removePerson(name);
	cout << "Record has been successfully deleted." << endl;
    getchar();
    getchar();
}

void delete_number() {
    char name[30];
	cout << "Enter the name you want to delete its number: ";
    cin >> name;
	phonebook.removeNumber(name);
    getchar();
    getchar();
}

void update_person() {
    char name[30];
	cout << "Enter the name you want to update: ";
    cin >> name;
	phonebook.updatePerson(name);
    getchar();
    getchar();
}

void update_number() {
    char name[30];
	cout << "Enter the name you want to update its number: ";
    cin >> name;
	phonebook.updateNumber(name);
    getchar();
    getchar();
}

void list_records() {
    phonebook.list();
    getchar();
    getchar();
}

void search_record() {
    char name[30];
    int found;
    cout << "Who do you want to search? ";
    cin >> name;
    found = phonebook.search(name);
    if(found == 0) cout << "No records found." << endl;
    getchar();
    getchar();
}
