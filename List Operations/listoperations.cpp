#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "listoperations.h"

using namespace std;

void List::create() {
    head = NULL;
    tail = NULL;
    personcount = 0;
}

void List::close() {
    makeEmpty();
}

void List::makeEmpty() {
    Phone_node *p;
    number *q;
    while(head) {
        p = head;
        head = head->next;
        q = p->phonenum;
        while(q) {
            p->phonenum = p->phonenum->next;
            delete q;
            q = p->phonenum;
        }
        delete p;
    }
    personcount = 0;
}

Phone_node * List::create_node(char *name) {
    Phone_node *newperson;

    newperson = new Phone_node;
    strcpy(newperson->name, name);
    newperson->next = NULL;
    newperson->previous = NULL;
    return newperson;
}

bool List::addPerson(char *newname) {
    Phone_node *traverse, *behind, *newperson;
    traverse = head;
    if(head == NULL) {
        newperson = create_node(newname);
        head = newperson;
        tail = newperson;
        personcount++;
        return true;
    }
    if(strcmp(newname, head->name) == 0) {
        return false;
    }
    if(strcmp(newname, head->name) < 0) {
        newperson = create_node(newname);
        newperson->next = head;
        head = newperson;
        (newperson->next)->previous = newperson;
        personcount++;
        return true;
    }
    while(traverse && (strcmp(newname, traverse->name) >= 0)) {
        if(strcmp(newname, traverse->name) == 0) {
            cout << "There is already a record in this name." << endl;
            return false;
        }
        // newname comes after traverse's name
        behind = traverse;
        traverse = traverse->next;
    }

    newperson = create_node(newname);
    if(traverse) {  // insert in between
        newperson->next = traverse;
        newperson->previous = behind;
        behind->next = newperson;
        traverse->previous = newperson;
    }
    else {  // insert to end
        tail->next = newperson;
        newperson->previous = tail;
        tail = newperson;
    }
    personcount++;
    return true;
}

bool List::addNumber(char *name, char *newphone, char *newtype) {
    Phone_node *traverse;
    number *newnum, *pn, *pn_tail;
    traverse = head;
    while(traverse) {
        if(strcmp(name, traverse->name) == 0) {
            newnum = new number;
            pn = traverse->phonenum;
            if(pn == NULL) {
                newnum->next = traverse->phonenum;
                traverse->phonenum = newnum;
                strcpy(newnum->num, newphone);
                strcpy(newnum->type, newtype);
                return true;
            }
            while(pn) {
                pn_tail = pn;
                pn = pn->next;
            }
            pn_tail->next = newnum;
            newnum->next = NULL;
            strcpy(newnum->num, newphone);
            strcpy(newnum->type, newtype);
            return true;
        }
        traverse = traverse->next;
    }
    cout << "There is no record in that name." << endl;
    return false;
}

void List::removePerson(char *name) {
    Phone_node *traverse, *behind;
    number *pn;
    traverse = head;
    int ordernum = 1;
    while(traverse) {
        if(strcmp(name, traverse->name) == 0) {
            if(ordernum == 1) {  // record found at the beginning
                head = head->next;
                pn = traverse->phonenum;
                while(pn) {
                    traverse->phonenum = pn->next;
                    delete pn;
                    pn = traverse->phonenum;
                }
                delete traverse;
                personcount--;
                return;
            }
            else {
                if(traverse->next) {
                    behind->next = traverse->next;
                    (traverse->next)->previous = behind;
                }
                else {
                    tail = traverse->previous;
                    tail->next = NULL;
                }
                pn = traverse->phonenum;
                while(pn) {
                    traverse->phonenum = pn->next;
                    delete pn;
                    pn = traverse->phonenum;
                }
                delete traverse;
                personcount--;
                return;
            }
        }
        ordernum++;
        behind = traverse;
        traverse = traverse->next;
    }
}

void List::removeNumber(char *name) {
    Phone_node *traverse;
    number *pn, *pn_behind;
    traverse = head;
    int ordernum, counter = 1;;
    while(traverse) {
        if(strcmp(name, traverse->name) == 0) {
            pn = traverse->phonenum;
            listNumbers(name);
            cout << "Please enter the index of number you want to delete: ";
            cin >> ordernum;
            while(pn) {
                if(ordernum <= 0) cout << "Invalid index." << endl;
                else if(ordernum == 1) {  // delete from beginning
                    traverse->phonenum = pn->next;
                    delete pn;
                    cout << "The phonenumber has been successfully deleted." << endl;
                    return;
                }
                else if(counter == ordernum) {
                    pn_behind->next = pn->next;
                    delete pn;
                    cout << "The phonenumber has been successfully deleted." << endl;
                    return;
                }
                counter++;
                pn_behind = pn;
                pn = pn->next;
            }
        }
        traverse = traverse->next;
    }
}

void List::updatePerson(char *name) {
    Phone_node *traverse, *behind;
    number *pn, *newnum;
    int counter = 1;
    char newname[30];
    traverse = head;
    while(traverse) {
        if(strcmp(name, traverse->name) == 0) {
            pn = traverse->phonenum;
            if(counter == 1) {  // found at the head of the list
                head = head->next;
                delete traverse;
                personcount--;
                break;
            }
            else {
                if(traverse->next) {
                    behind->next = traverse->next;
                    (traverse->next)->previous = behind;
                }
                else {
                    tail = traverse->previous;
                    tail->next = NULL;
                }
                delete traverse;
                personcount--;
                break;
            }
        }
        counter++;
        behind = traverse;
        traverse = traverse->next;
    }
    cout << "Enter a new name: ";
    cin >> newname;
    addPerson(newname);
    newnum = new number;
    newnum = pn;
    traverse = head;
    while(traverse) {
        if(strcmp(newname, traverse->name) == 0) {
            traverse->phonenum = newnum;
            cout << "The name has been updated." << endl;
            return;
        }
        traverse = traverse->next;
    }
}

void List::updateNumber(char *name) {
    Phone_node *traverse;
    number *pn, *pn_behind;
    traverse = head;
    char newnum[15], newtype[7];
    int ordernum, counter = 1, number_counter;
    while(traverse) {
        if(strcmp(name, traverse->name) == 0) {
            pn = traverse->phonenum;
            number_counter = listNumbers(name);
            cout << "Please enter the index of number you want to update: ";
            cin >> ordernum;
            while(pn) {
                if(ordernum <= 0 || ordernum > number_counter) {
                    cout << "Error: Invalid index." << endl;
                    return;
                }
                else if(counter == ordernum) {
                    cout << "Enter the type of the new phonenumber: ";
                    cin >> newtype;
                    cout << "Enter the new phonenumber: ";
                    cin >> newnum;
                    strcpy(pn->type, newtype);
                    strcpy(pn->num, newnum);
                    cout << "The phonenumber has been successfully updated." << endl;
                    return;
                }
                counter++;
                pn_behind = pn;
                pn = pn->next;
            }
        }
        traverse = traverse->next;
    }
}

int List::search(char *target) {
    Phone_node *traverse;
    number *pn;
    int counter = 0;
    int found = 0;
    traverse = head;
    bool all = false, flag1 = false, flag2 = false;

    if(target[0] == '*') all = true;

    while(traverse) {
        counter++;
        flag1 = false;
        if(all) {
            cout << counter << ". " << traverse->name << endl;
            pn = traverse->phonenum;
            while(pn) {
                cout << "\t" << pn->type << ": " << pn->num << endl;
                pn = pn->next;
            }
            found++;
        }
        else if(strncmp(target, traverse->name, strlen(target)) == 0) {
            flag1 = true;
            flag2 = true;
            found++;
            cout << counter << ". record: " << traverse->name << endl;
            pn = traverse->phonenum;
            while(pn) {
                cout << "\t" << pn->type << ": " << pn->num << endl;
                pn = pn->next;
            }
        }
        if(!flag1 && flag2) return found;
        traverse = traverse->next;
    }
    return found;
}

void List::list() {
    char name[] = "*";
    search(name);
}

int List::listNumbers(char *name) {
    Phone_node *traverse;
    number *pn;
    int counter = 1;
    traverse = head;
    while(traverse) {
        if(strcmp(name, traverse->name) == 0) {
            pn = traverse->phonenum;
            while(pn) {
                cout << counter << ". " << pn->type << ": " << pn->num << endl;
                pn = pn->next;
                counter++;
            }
            return counter - 1;
        }
        traverse = traverse->next;
    }
    if(counter) cout << "There is no record in that name." << endl;
    return counter - 1;
}
