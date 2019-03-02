#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "listoperations.h"

using namespace std;

void all_lower(char *, int);

void List::create() {
    head = NULL;
    surnamecount = 0;
}

void List::close() {
    deleteAll();    // before terminating the program, delete all data from memory
}
// a function that deletes everything from memory
void List::deleteAll() {
    // Initializing required variables
    surnameMap *temp = head;
    studentInfo *studentinformation;
    if(head != NULL) {
        do{
            studentinformation = temp->student;
            if(studentinformation != NULL) {
                do{
                    delete[] studentinformation->name;  // deleting from memory
                    delete[] studentinformation->surname;  // deleting from memory
                    delete[] studentinformation->email;  // deleting from memory
                    delete studentinformation;  // deleting from memory
                    studentinformation = studentinformation->next;
                }while(studentinformation != NULL);
            }
            delete[] temp->surname;  // deleting from memory
            delete temp;  // deleting from memory
            temp = temp->next;
        }while(temp != head);
    }
    surnamecount = 0;
}

surnameMap * List::create_node(char *surname) {
    surnameMap *newsurname;

    newsurname = new surnameMap;    // allocating new memory for surnameMap node
    newsurname->surname = new char[strlen(surname) + 1];    // getting required space for surname
    strcpy(newsurname->surname, surname);   // copying surname to its struct
    newsurname->student = NULL;
    newsurname->next = NULL;
    return newsurname;  // returning the newsurname
}

bool List::insertNewRecord(char *name_toadd, char *surname_toadd) {
    surnameMap *traverse, *behind, *newsurname;
    if(head == NULL) {  // first node is being added
        newsurname = create_node(surname_toadd);    // creating a new node for new surname
        head = newsurname;
        newsurname->next = head;
        surnamecount++;
        create_email(head, name_toadd, surname_toadd);  // creating a new email adress for the student
        return true;
    }
    if(strcmp(surname_toadd, head->surname) == 0) {
        create_email(head, name_toadd, surname_toadd);
        return true;
    }
    if(strcmp(surname_toadd, head->next->surname) < 0) {    // add to after head
        newsurname = create_node(surname_toadd);    // creating a new node for new surname
        newsurname->next = head->next;
        head->next = newsurname;
        surnamecount++;
        create_email(head->next, name_toadd, surname_toadd);  // creating a new email adress for the student
        return true;
    }
    if(strcmp(surname_toadd, head->next->surname) == 0) {
        create_email(head->next, name_toadd, surname_toadd);  // creating a new email adress for the student
        return true;
    }

    traverse = head->next;
    do {
        // newnode's surname comes after traverse's
        behind = traverse;
        traverse = traverse->next;
    }while(traverse != head->next && (strcmp(surname_toadd, traverse->surname) >= 0));
    if(strcmp(surname_toadd, behind->surname) == 0) {
        create_email(behind, name_toadd, surname_toadd);  // creating a new email adress for the student
        return true;
    }

    newsurname = create_node(surname_toadd);    // creating a new node for new surname
    if(traverse != head->next) {  // insert in between
        newsurname->next = traverse;
        behind->next = newsurname;
        create_email(newsurname, name_toadd, surname_toadd);  // creating a new email adress for the student
    }
    else {  // insert to end
        newsurname->next = head->next;
        head->next = newsurname;
        head = newsurname;
        create_email(newsurname, name_toadd, surname_toadd);  // creating a new email adress for the student
    }
    surnamecount++;
    return true;
}

bool List::create_email(surnameMap *location, char *firstname, char *lastname) {
    // Initializing required variables
    studentInfo *traverse, *behind, *newnode;
    int i, counter = 1, counter2 = 2;
    char name_char[30], tempname[30];
    char surname_char[30];
    char new_mail[100];

    strcpy(name_char, firstname);  // copying name to a new char array
    strcpy(surname_char, lastname); // copying surname to a new char array
    all_lower(name_char, strlen(name_char));
    all_lower(surname_char, strlen(surname_char));

    sprintf(new_mail, "%s%s", surname_char, "@itu.edu.tr");

    traverse = location->student;
    newnode = new studentInfo;  // allocating new space from memory for a new student

    newnode->name = new char[strlen(firstname) + 1];  // allocating memory for its name
    strcpy(newnode->name, firstname);   // copying name to its struct
    newnode->surname = new char[strlen(lastname) + 1];  // allocating memory for its surname
    strcpy(newnode->surname, lastname);   // copying surname to its struct

    if(traverse == NULL) {  // if the first email will be created in that surname
        newnode->email = new char[strlen(new_mail) + 1];  // allocating memory for its email
        strcpy(newnode->email, new_mail);   // copying email to its struct
        location->student = newnode;
        newnode->next = NULL;   // since it is first student in that surname, its next should be NULL
        newnode->previous = NULL;
        return true;
    }
    while(traverse && strcmp(new_mail, traverse->email) >= 0) {
        if(strcmp(new_mail, traverse->email) == 0) {
            for(i = 0; i < counter; i++) {  // getting letters in order to add to email
                tempname[i] = name_char[i];
            }
            tempname[i] = '\0';
            if(counter <= strlen(name_char)) {
                counter++;
                sprintf(new_mail, "%s%s@itu.edu.tr", surname_char, tempname);  // if there is a similar email, then add a new letter from student's name
            }
            else {
                sprintf(new_mail, "%s%s%d@itu.edu.tr", surname_char, tempname, counter2);   // if there is still a similar email after adding student's name, then add a number
                counter2++;
            }
        }
        behind = traverse;
        traverse = traverse->next;
    }
    newnode->email = new char[strlen(new_mail) + 1];  // allocating memory for its email
    strcpy(newnode->email, new_mail);   // copying email to its struct

    if(traverse) {  // insert in between
        newnode->next = traverse;
        newnode->previous = behind;
        behind->next = newnode;
        traverse->previous = newnode;
    }
    else {  // insert to end
        behind->next = newnode;
        newnode->previous = behind;
        newnode->next = NULL;
    }
    return true;
}

void List::insertAll() {
    char filename[] = "newStudentsList.txt";
    ifstream students_file(filename);  // opening the file for reading
    // Initializing required variables
    string str;
    char *name, *surname;

    while(getline(students_file, str)) {    // reading the file line by line
        name = strtok(&str[0], "\t");   // getting the name from string
        surname = strtok(NULL, "\n");   // getting the surname from string
        surname[strlen(surname)] = '\0';
        insertNewRecord(name, surname); // inserting the student into the list
    }
    students_file.close();  // closing the file
}

bool List::deleteStudent(char *name, char *surname) {
    // Initializing required variables
    surnameMap *temp;
    studentInfo *traverse, *behind;
    temp = head->next;
    traverse = temp->student;
    int ordernum, counter = 1, found;
    char choice;

    if(temp != NULL) {
        do{
            if(strcmp(surname, temp->surname) == 0) {
                found = search(temp, name);
                if(found == 0) {  // if there is no record in that name
                    cout << "No record found." << endl;
                    return false;
                }
                cout << "\nPlease enter the index of the student: ";
                cin >> ordernum;    // taking the index of the student that will be deleted
                if(ordernum <= 0)   {
                    cout << "Invalid index." << endl;
                    return false;
                }
                else if(ordernum == 1) {    // delete from beginning
                    if(temp->student->next == NULL) {  // if the surname node has only 1 student, delete the surname node
                        deleteSurnameNode(temp->surname);
                        return true;
                    }
                    else {  // otherwise, delete only the student from the beginning
                        cout << "Are you really sure you want to do this? (Y/N) ";
                        cin >> choice;
                        if(choice == 'Y'  || choice == 'y') {
                            delete[] traverse->name;  // deleting from memory
                            delete[] traverse->surname;  // deleting from memory
                            delete[] traverse->email;  // deleting from memory
                            temp->student = temp->student->next;  // changing head to next one
                            temp->student->previous = NULL;  // assigning its previous to NULL
                            delete traverse;  // deleting from memory
                            return true;  // delete operation was done successfully
                        }
                        else if(choice == 'N' || choice == 'n') return false;
                        else {
                            cout << "Invalid choice." << endl;
                            return false;
                        }
                    }
                }
                do{ // if the student is not at the beginning, search it through surname node
                    counter++;
                    behind = traverse;
                    traverse = traverse->next;
                }while(traverse != NULL && (counter < ordernum));
                if(counter < ordernum) {    // given record num too large
                    cout << "Could not find record." << endl;
                    return false;
                }
                else {  // record found
                    cout << "Are you really sure you want to do this? (Y/N): ";
                    cin >> choice;
                    if(choice == 'Y'  || choice == 'y') {
                        behind->next = traverse->next;
                        if(traverse->next)
                            traverse->next->previous = traverse->previous;
                        delete[] traverse->name;    // deleting from memory
                        delete[] traverse->surname;    // deleting from memory
                        delete[] traverse->email;    // deleting from memory
                        delete traverse;    // deleting from memory
                        return true;    // delete operation was done successfully
                    }
                    else if(choice == 'N' || choice == 'n') return false;
                    else {
                        cout << "Invalid choice." << endl;
                        return false;
                    }
                }
            }
            temp = temp->next;  // going to next surname on the surnameMap
            traverse = temp->student;  // changing studentInfo each time
        }while(temp != head->next);  // do until reaching head->next
    }
    return false;  // if there is no record in that surname, return false
}

bool List::deleteSurnameNode(char *surname) {
    // Initializing required variables
    surnameMap *traverse, *behind;
    studentInfo *studentinformation;
    traverse = head->next;
    behind = head;
    studentinformation = traverse->student;
    char choice;

    if(traverse != NULL) {  // checking if the surnameMap is empty
        do{
            if(strcmp(traverse->surname, surname) == 0) {
                cout << "Are you really sure you want to do this? (Y/N) ";
                cin >> choice;
                if(choice == 'Y' || choice == 'y') {
                    do{
                        delete[] studentinformation->name;  // deleting from memory
                        delete[] studentinformation->surname;  // deleting from memory
                        delete[] studentinformation->email;  // deleting from memory
                        delete studentinformation;  // deleting from memory
                        studentinformation = studentinformation->next;
                    }while(studentinformation != NULL);
                    if(traverse == head) {  // if the surname that will be deleted is head, then make old one's previous new head
                        head = behind;
                    }
                    behind->next = traverse->next;
                    delete traverse;  // deleting from memory
                    surnamecount--; // decrementing number of surnames
                    return true;    // deleting operation was done successfully
                }
                else if(choice == 'N' || choice == 'n') return false;
                else {
                    cout << "\nInvalid choice." << endl;
                    return false;
                }
            }
            behind = traverse;
            traverse = traverse->next;
            studentinformation = traverse->student;
        }while(traverse != head->next);
    }
    cout << "\nThe surname node could not be found." << endl;
    return false;   // no surname found
}

bool List::updateList(char *name, char *surname) {
    char new_name[30];
    char new_surname[30];
    char choice;

    if(!deleteStudent(name, surname)) return false;

    cout << "Do you want to update his/her name or surname or both? (N/S/B): ";
    cin >> choice;

    if(choice == 'N' || choice == 'n') {
        cout << "\nEnter a new name for the student: ";
        cin >> new_name;
        insertNewRecord(new_name, surname);
        return true;
    }
    else if(choice == 'S' || choice == 's') {
        cout << "Enter a new surname for the student: ";
        cin >> new_surname;
        insertNewRecord(name, new_surname);
        return true;
    }
    else if(choice == 'B' || choice == 'b') {
        cout << "Enter a new name for the student: ";
        cin >> new_name;
        cout << "Enter a new surname for the student: ";
        cin >> new_surname;
        insertNewRecord(new_name, new_surname);
        return true;
    }
}

void List::writeToFile() {
    surnameMap *temp = head->next;
    studentInfo *traverse = temp->student;

    ofstream emailList;

    emailList.open("emailList.txt");  // opening the file for writing

    if(temp != NULL) {
        do{
            if(traverse != NULL) {
                do{
                    emailList << traverse->name << " " << traverse->surname << "\t" << traverse->email << "\n";
                    traverse = traverse->next;
                }while(traverse != NULL);
            }
            temp = temp->next;
            traverse = temp->student;
        }while(temp != head->next);
    }
    emailList.close();
}

int List::search(surnameMap *surname_location, char *target_name) {
    if(surnamecount == 0) return 0;
    surnameMap *traverse = surname_location;
    studentInfo *studentinformation = traverse->student;
    int counter = 0, found = 0;
    bool flag1 = false, flag2 = false;

    if(studentinformation != NULL) {
        do{
            counter++;
            flag1 = false;
            if(strncmp(target_name, studentinformation->name, strlen(target_name)) == 0) {
                found++;
                cout << counter << ". " << studentinformation->name << " " << studentinformation->surname << "\t" << studentinformation->email << endl;
                flag1 = true;   // indicating whether or not any person found
                flag2 = true;   // indicating the program is still finding new person
            }
            if(!flag1 && flag2) return found;
            studentinformation = studentinformation->next;
        }while(studentinformation != NULL);
    }
    return found;
}

void List::printList() {
    surnameMap *temp;
    studentInfo *traverse;

    if(surnamecount == 0) {
        cout << "There is no record." << endl;
        return;
    }
    temp = head->next;
    traverse = temp->student;

    if(temp != NULL) {
        do{
            cout << temp->surname << endl;
            if(traverse != NULL) {
                do{
                    cout << "\t" << traverse->name << " " << traverse->surname << "\t" << traverse->email << endl;
                    traverse = traverse->next;
                }while(traverse != NULL);
            }
            temp = temp->next;
            traverse = temp->student;
        }while(temp != head->next);
    }
}

// a function that takes a word and converts all its letters to lower case
void all_lower(char *word, int n) {
	int i;  // counter
	for (i = 0; i < n; i++) {
		if(isupper(word[i]))
			word[i] = word[i] - ('A' - 'a');  // converting to lowercase letter
	}
}
