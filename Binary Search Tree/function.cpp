#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

using namespace std;

void tree::create() {
	root = NULL;
	node_counter = 0;
}

void tree::close() {
	emptytree(root);
}

void tree::emptytree(Phone_node *p) {
	number *num;
	if (p) {
		if (p->left != NULL) {
			emptytree(p->left);
			p->left = NULL;
		}
		if (p->right != NULL) {
			emptytree(p->right);
			p->right = NULL;
		}
		num = p->phonenum;
		while (num) {
			p->phonenum = p->phonenum->next;
			delete num;
			num = p->phonenum;
		}
		delete p;
		node_counter--;
	}
}

Phone_node *tree::create_node(char *name) {
	Phone_node *newperson;

	newperson = new Phone_node;
	newperson->name = new char[strlen(name) + 1];
	strcpy(newperson->name, name);
	newperson->phonenum = NULL;
	newperson->right = NULL;
	newperson->left = NULL;
	return newperson;
}

void tree::add(char *name, char *p_number) {
	Phone_node *traverse, *newnode;
	number *num;
	traverse = root;
	int comparison;
	bool added = false;
	if (root == NULL) {
		// first node being added
		newnode = create_node(name);
		addNumber(newnode, p_number);
		root = newnode;
		node_counter++;
		return;
	}
	newnode = search(name);
	if (newnode == NULL) {
		while (traverse != NULL && !added) {
			comparison = strcmp(name, traverse->name);
			if (comparison < 0) {
				if (traverse->left != NULL)
					traverse = traverse->left;
				else {
					newnode = create_node(name);
					addNumber(newnode, p_number);
					traverse->left = newnode;
					added = true;
				}
			}
			else if (comparison > 0) {
				if (traverse->right != NULL)
					traverse = traverse->right;
				else {
					newnode = create_node(name);
					addNumber(newnode, p_number);
					traverse->right = newnode;
					added = true;
				}
			}
		}
		node_counter++;
	}
	else {
		addNumber(newnode, p_number);
	}
}

bool tree::addNumber(Phone_node *person, char *newnum) {
	number *newnumber, *traverse, *behind;
	traverse = behind = person->phonenum;
	newnumber = new number;
	newnumber->phonenum = new char[strlen(newnum) + 1];
	strcpy(newnumber->phonenum, newnum);
	if (traverse == NULL) {
		person->phonenum = newnumber;
		newnumber->next = NULL;
		return true;
	}
	while (traverse) {
		behind = traverse;
		traverse = traverse->next;
	}
	behind->next = newnumber;
	newnumber->next = NULL;
	return true;
}

Phone_node *tree::search(char *search_name) {
	Phone_node *traverse;
	number *num;
	traverse = root;
	int comparison;
	bool found = false;
	bool all = false;
	while (traverse && !found) {
		comparison = strcmp(search_name, traverse->name);
		if (comparison < 0)
			traverse = traverse->left;
		else if (comparison > 0)
			traverse = traverse->right;
		else // if names are equal, record found
			found = true;
	}
	if (found == true)	return traverse;
	else	return NULL;
}

void tree::print_inorder(Phone_node *nptr) {
	number *num;
	if (nptr) {
		print_inorder(nptr->left);
		cout << ">> " << nptr->name << endl;
		num = nptr->phonenum;
		while (num) {
			cout << "\t" << num->phonenum << endl;
			num = num->next;
		}
		cout << endl;
		print_inorder(nptr->right);
	}
}

bool tree::remove(char *remove_name, char mode) {
	Phone_node *traverse, *parent;
	number *num;
	traverse = parent = root;
	num = traverse->phonenum;
	int comparison;
	bool found = false;
	char direction = 'k';
	while (traverse && !found) {
		comparison = strcmp(remove_name, traverse->name);
		if (comparison < 0) {
			parent = traverse;
			direction = 'l';
			traverse = traverse->left;
		}
		else if (comparison) {
			parent = traverse;
			direction = 'r';
			traverse = traverse->right;
		}
		else	// found record to remove
			found = true;
	}
	if (found) {
		if (traverse->left == NULL && traverse->right == NULL) {	// if the node is a child
			switch (direction) {
			case 'l':
				parent->left = NULL;
				break;
			case 'r':
				parent->right = NULL;
				break;
			default:
				root = NULL;
				break;
			}
		}
		else if (traverse->right == NULL) {	// if the node has only a left child
			switch (direction) {
			case 'l':
				parent->left = traverse->left;
				break;
			case 'r':
				parent->right = traverse->left;
				break;
			default:
				root = traverse->left;
				break;
			}
		}
		else if (traverse->left == NULL) {	// if the node has only a right child
			switch (direction) {
			case 'l':
				parent->left = traverse->right;
				break;
			case 'r':
				parent->right = traverse->right;
				break;
			default:
				root = traverse->right;
				break;
			}
		}
		else {	// if the node is a parent and has two child
			Phone_node *q = traverse->right;
			while (q->left)
				q = q->left;
			q->left = traverse->left;
			switch (direction) {
			case 'l':
				parent->left = traverse->right;
				break;
			case 'r':
				parent->right = traverse->right;
				break;
			default:
				root = traverse->right;
				break;
			}

		}
		if (mode == '+') {
			num = traverse->phonenum;
			while (num) {
				traverse->phonenum = traverse->phonenum->next;
				delete num;
				num = traverse->phonenum;
			}
		}
		delete traverse;
		return true;
	}
	else
		return false;
}

bool tree::update(char *old_name, char *new_name) {
	Phone_node *temp, *temp2;
	number *num;
	temp = search(old_name);
	temp2 = search(new_name);
	if (temp == NULL) {
		return false;
	}
	if (temp2 != NULL) {	// if the new name is already in the phonebook, then concatenate both record
		num = temp2->phonenum;
		while (num->next)
			num = num->next;
		num->next = temp->phonenum;
	}
	else {	// create a new record and assign the number of old's numbers to the new one
		add(new_name, temp->phonenum->phonenum);
		temp->phonenum = temp->phonenum->next;
		temp2 = search(new_name);
		temp2->phonenum->next = temp->phonenum;
	}
	remove(old_name, '-');	// '-' means that delete only the name not the numbers of the person
	return true;
}