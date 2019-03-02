#include <iostream>
#include "stack_struct.h"
#include "queue_struct.h"

using namespace std;

#define NumOfAreas 4
int N = 1;

void Initialization();
void Close();
void print_menu();
bool do_operation(char choice);
bool AddNewCar(char []);
bool TakeTheCarOut();
void ShowThePark();
int IsInThePark(LicensePlate license_plate);

Stack Park[NumOfAreas];
Queue TemporaryArea;

int main() {
	Initialization();

	cout << " Enter the capacity of the areas in the park: ";
	cin >> N;

	char choice;
	bool finish = false;
	do {
		print_menu();
		cin >> choice;
		finish = do_operation(choice);
	} while (finish);
	Close();
	return 0;
}

void Initialization() {
	for (int i = 0; i < 4; i++)
		Park[i].create();
	TemporaryArea.create();
	return;
}

void Close() {
	for (int i = 0; i < 4; i++)
		Park[i].close();
	TemporaryArea.close();
	return;
}

void print_menu() {
	//system("cls"); //linux'ta ekran temizleme icin system("clear"); kullaniniz
	system("cls");
	cout << "\nPlease, choose an operation.\n" << endl;
	cout << "\t1. Add a new car" << endl;
	cout << "\t2. Take out a car" << endl;
	cout << "\t3. Show the park" << endl;
	cout << "\t4. Exit the application" << endl << endl;
	cout << "Enter an option {1, 2, 3, 4}: ";
}

bool do_operation(char choice) {
	bool flag = true;
	if (choice == '1') {
		char license[50];
		cout << "\nEnter the license of the car: ";
		cin.ignore(1000, '\n');
		cin.getline(license, 50);
		AddNewCar(license);
	}
	else if (choice == '2') TakeTheCarOut();
	else if (choice == '3') ShowThePark();
	else if (choice == '4') flag = false;
	return flag;
}

bool AddNewCar(char license[]) {
	if (Park[0].counter < N) Park[0].push(license);  // if first area is available, put it there
	else if (Park[1].counter < N) Park[1].push(license);  // if second area is available, put it there
	else if (Park[2].counter < N) Park[2].push(license);  // if third area is available, put it there
	else if (Park[3].counter < N) Park[3].push(license);  // if fourth area is available, put it there
	else {  // otherwise the park is full
		cout << "Park is full. You cannot add a new car.\n";
		getchar();
		getchar();
		return false;
	}
	return true;
}

bool TakeTheCarOut() {
	Node *temp;
	char license[50];
	char license_plate[50];
	bool removed = false;
	cout << "Enter the license plate of the car that you want to take out: ";
	cin.ignore(1000, '\n');
	cin.getline(license_plate, 50);

	int area = IsInThePark(license_plate);
	if (area == -1) {
		cout << "This car is not in the park." << endl;
		getchar();
		getchar();
		return false;
	}
	else {
		while (strcmp(Park[area].head->data, license_plate) != 0) {
			temp = Park[area].top();
			strcpy(license, temp->data);
			Park[area].pop();
			ShowThePark();
			for (int i = 0; i < NumOfAreas; i++) {
				if (i == area) continue;
				else {
					if (Park[i].counter < N) { // if there is a space in other areas, put it there
						Park[i].push(license);
						removed = true;
						break;
					}
				}
			}
			if (!removed) { // if all areas are full, put it into temporary area
				TemporaryArea.enqueue(license);
			}
			removed = false;
			ShowThePark();
		}
		Park[area].pop(); // take the car out
		ShowThePark();
		while (!TemporaryArea.isempty()) {  // if there are cars in temporary area, put back them into areas
			AddNewCar(TemporaryArea.dequeue());
			ShowThePark();
		}
	}
	return true;
}

void ShowThePark() {
	Node *temp;
	Node *temp0 = Park[0].head, *temp1 = Park[1].head, *temp2 = Park[2].head, *temp3 = Park[3].head;
	LicensePlate license;
	cout << endl;
	int max = 0, counter, i;
	for (i = 0; i < NumOfAreas; i++) {
		if (max < Park[i].counter)
			max = Park[i].counter;
	}
	counter = max;

	while (counter > 0) {
		if (counter > Park[0].counter) {
			cout << "|\t\t|\t";
		}
		else {
			cout << "|\t" << temp0->data << "\t|\t";
			temp0 = temp0->next;
		}
		if (counter > Park[1].counter) {
			cout << "|\t\t|\t";
		}
		else {
			cout << "|\t" << temp1->data << "\t|\t";
			temp1 = temp1->next;
		}
		if (counter > Park[2].counter) {
			cout << "|\t\t|\t";
		}
		else {
			cout << "|\t" << temp2->data << "\t|\t";
			temp2 = temp2->next;
		}
		if (counter > Park[3].counter) {
			cout << "|\t\t|\t";
		}
		else {
			cout << "|\t" << temp3->data << "\t|\t";
			temp3 = temp3->next;
		}
		cout << endl;
		counter--;
	}
	cout << "\tArea 1\t\t\tArea 2\t\t\tArea 3\t\t\tArea 4\t" << endl;
	cout << endl;

	temp = TemporaryArea.front;
	cout << "Temporary Area" << endl;
	
	if (TemporaryArea.isempty()) cout << "  Empty\n";
	else {
		while (temp) {
			cout << temp->data << endl;
			temp = temp->next;
		}
	}
	getchar();
	getchar();
	return;
}

int IsInThePark(LicensePlate license_plate) {
	Node *temp;
	int area;
	bool break_flag = false;
	for (int i = 0; i < 4; i++) {
		temp = Park[i].top();
		if (!Park[i].isempty()) {
			while (temp) {
				if (strcmp(license_plate, temp->data) == 0) {
					break_flag = true;
					area = i;
					break;
				}
				temp = temp->next;
			}
		}
		if(break_flag) break;
	}
	if (break_flag)
		return area;
	else
		return -1;
}