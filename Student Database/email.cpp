/* @Author  
 * Student Name: İskender Akyüz 
 * Student ID : 150150150
 * Date: 30.10.2017  
 */

//  The program was not designed to work with Turkish characters.


#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "listoperations.h"

using namespace std;

List studentList;
bool create_flag = false, insert_flag = false;

void print_menu();
bool do_operation(char);
void create();
void insert_all();
void add_new_record();
void delete_record();
void delete_surname();
void update_student();
void write_into_file();
void list_records();

int main() {
    setlocale(LC_ALL, "Turkish");
    char choice;
    bool finish = false;
    do {
        print_menu();
        cin >> choice;
        finish = do_operation(choice);
    } while (finish);
    studentList.deleteAll();
    return 0;
}

void print_menu(){
	//system("cls"); //linux'ta ekran temizleme icin system("clear"); kullaniniz
	system("clear");
	cout << "\ne-mail Address Program\n" << endl;
	cout << "\t1. Create" << endl;
	cout << "\t2. Insert All" << endl;
	cout << "\t3. Insert New Record" << endl;
	cout << "\t4. Delete Student" << endl;
	cout << "\t5. Delete Surname Node" << endl;
    cout << "\t6. Update" << endl;
    cout << "\t7. Write to File" << endl;
    cout << "\t8. List" << endl;
	cout << "\t9. Exit the application" << endl << endl;
	cout << "Enter an option {1, 2, 3, 4, 5, 6, 7, 8, 9}: ";
}

bool do_operation(char choice) {
	bool flag = true;
	if (choice == '1') {
        if(!create_flag)
            create();
        else {
            cout << "\nThe surname map has already been created. You cannot do it again." << endl;
            getchar();
            getchar();
        }
    }
	else if (choice == '2') {
        if(!insert_flag)
            insert_all();
        else {
            cout << "\nThe students in the text file has already been inserted. You cannot do it again." << endl;
            getchar();
            getchar();
        }
    }
	else if (choice == '3') add_new_record();
	else if (choice == '4') delete_record();
	else if(choice == '5') delete_surname();
    else if(choice == '6') update_student();
    else if(choice == '7') write_into_file();
    else if(choice == '8') list_records();
	else if (choice == '9') flag = false;
	return flag;
}

void create() {
    studentList.create();
    create_flag = true;
    cout << "\nThe list has been created." << endl;
    getchar();
    getchar();
}

void insert_all() {
    if(!create_flag) {
        cout << "\nBefore inserting students from file, you should create a surnameMap list." << endl;
    }
    else {
        studentList.insertAll();
        insert_flag = true;
        cout << "\nAll students in the txt file has been inserted." << endl;
    }
    getchar();
    getchar();
}

void add_new_record() {
    char new_name[30], new_surname[30];
    if(!create_flag) {
        cout << "\nBefore inserting a new student, you should create a surnameMap list." << endl;
    }
    else {
        cout << "\nEnter the information of the student." << endl;
        cout << "Name: ";
        cin.ignore(1000, '\n');
        cin.getline(new_name, 30);
        cout << "Surname: ";
        cin >> new_surname;
        if(studentList.insertNewRecord(new_name, new_surname)) {
            cout << "\nNew record has been successfully added." << endl;
        }
        else {
            cout << "\nAn error has been occured." << endl;
        }
    }
    getchar();
    getchar();
}

void delete_record() {
    char name[30], surname[30];
    cout << "\nEnter the information of the student that you want to delete." << endl;
    cout << "Name: ";
    cin.ignore(1000, '\n');
    cin.getline(name, 30);
    cout << "Surname: ";
    cin >> surname;
    if(studentList.deleteStudent(name, surname)) {
        cout << "\nThe student has been successfully deleted." << endl;
    }
    else {
        cout << "\nAn error has been occured, so the student could not be deleted." << endl;
    }
    getchar();
    getchar();
}

void delete_surname() {
    char surname[30];
    cout << "\nEnter the surname you want to delete: ";
    cin >> surname;
    if(studentList.deleteSurnameNode(surname)) {
        cout << "\nThe surname node has been successfully deleted." << endl;
    }
    getchar();
    getchar();
}

void update_student() {
    char name[30], surname[30];
    cout << "\nEnter the information of the student that you want to update." << endl;
    cout << "Name: ";
    cin.ignore(1000, '\n');
    cin.getline(name, 30);
    cout << "Surname: ";
    cin >> surname;
    if(studentList.updateList(name, surname)) {
        cout << "\nThe student has been successfully updated." << endl;
    }
    else {
        cout << "\nAn error has been occured, so the student could not been updated." << endl;
    }
    getchar();
    getchar();
}

void write_into_file() {
    studentList.writeToFile();
    cout << "\nAll students has been written into a txt file." << endl;
    getchar();
    getchar();
}

void list_records() {
    studentList.printList();
    getchar();
    getchar();
}

// by marnop