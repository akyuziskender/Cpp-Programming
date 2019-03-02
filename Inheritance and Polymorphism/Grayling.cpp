#include "Grayling.h"

Grayling::Grayling() {	// Dfeault Constructor
	age = 0;
	is_alive = false;
	is_mutant = false;
}

Grayling::Grayling(char gender, string name) {	// Constructor
	age = 0;
	this->name = name;
	this->gender = gender;
	is_alive = true;
	is_mutant = false;
}

Grayling::Grayling(const Grayling &obj_in, char gender_in, string name_in) {	// Cpoy Constructor
	age = obj_in.age;
	name = name_in;
	gender = gender_in;
	is_alive = obj_in.is_alive;
	is_mutant = obj_in.is_mutant;
	mutated_to = obj_in.mutated_to;
	MPI = obj_in.MPI;
	MP = obj_in.MP;
	mutate_at = obj_in.mutate_at;
}

void Grayling::print() const {}	// virtual function

void Grayling::givebirth() {}	// virtual function

void Grayling::aging() {}	// virtual function

Grayling1::Grayling1(char gender_in, string name_in) : Grayling(gender_in, name_in) {	// Constructor
	MPI = 30;
	MP = 0;
	mutate_at = 60;
}

Grayling1::Grayling1(const Grayling1 &obj_in, char gender, string name) : Grayling(obj_in, gender, name) {}	// Copy Constructor

void Grayling1::print() const {	// virtual function
	cout << "- Grayling 1 -> Age: " << age << " Name: " << name << " G: " << gender << " MPI: " << MPI << " MP: " << MP << " Mutate at: " << mutate_at << endl;
}

void Grayling1::givebirth() {	// virtual function
	if (is_alive) {
		if (gender == 'm' || gender == 'M')
			cout << "- Trying to GIVE BIRTH BUT " << name << " has no abiltiy to give birth because of its gender!" << endl;
		else if (MPI == 50) {
			cout << "- Trying to GIVE BIRTH BUT " << name << " has no ability to give birth. It caused the death of it." << endl;
			is_alive = false;
		}
		else {
			cout << "- " << name << " gave birth to " << (MPI == 30 ? 2 : 1) << " offsprings!" << endl;
		}
	}
	else
		cout << "- Trying to GIVE BIRTH BUT " << name << " is not alive" << endl;
}

void Grayling1::aging() {	// virtual function
	if (is_alive) {
		age++;
		MP += MPI;
		cout << "- AGING: Name: " << name << " -> " << (is_mutant ? mutated_to : "") << " Age: " << age << " MPI: " << MPI << " MP: " << MP << endl;
		if ((age == 5 && MPI == 30) || (age == 4 && MPI == 40) || (age == 3 && MPI == 50)) {	// checking if it is dead
			cout << "- " << name << " is dead because of AGING!" << endl;
			is_alive = false;
		}
		if (is_alive && MP >= mutate_at) {	// checking mutation
			if (MP < 80) {
				mutated_to = "Grayling2";
				MPI = 40;
				MP = 0;
				mutate_at = 80;
			}
			else {
				mutated_to = "Grayling3";
				MPI = 50;
				MP = 0;
				mutate_at = 100;
			}
			is_mutant = true;
			cout << "- Mutated TO: " << mutated_to << endl;
		}
	}
	else
		cout << "- Trying to AGING BUT " << name << " is not alive" << endl;
}

Grayling2::Grayling2(char gender_in, string name_in) : Grayling(gender_in, name_in) {	// Constructor
	MPI = 40;
	MP = 0;
	mutate_at = 80;
}

Grayling2::Grayling2(const Grayling2 &obj_in, char gender, string name) : Grayling(obj_in, gender, name) {}	// Copy Constructor

void Grayling2::print() const {	// virtual function
	cout << "- Grayling 2 -> Age: " << age << " Name: " << name << " G: " << gender << " MPI: " << MPI << " MP: " << MP << " Mutate at: " << mutate_at << endl;
}

void Grayling2::givebirth() {	// virtual function
	if (is_alive) {
		if (gender == 'm' || gender == 'M')
			cout << "- Trying to GIVE BIRTH BUT " << name << " has no abiltiy to give birth because of its gender!" << endl;
		else if (MPI == 50) {
			cout << "- Trying to GIVE BIRTH BUT " << name << " has no ability to give birth. It caused the death of it." << endl;
			is_alive = false;
		}
		else {
			cout << "- " << name << " gave birth to 1 offsprings!" << endl;
		}
	}
	else
		cout << "- Trying to GIVE BIRTH BUT " << name << " is not alive" << endl;
}

void Grayling2::aging() {	// virtual function
	if (is_alive) {
		age++;
		MP += MPI;
		cout << "- AGING: Name: " << name << " -> " << (is_mutant ? mutated_to : "") << " Age: " << age << " MPI: " << MPI << " MP: " << MP << endl;
		if ((age == 4 && MPI == 40) || (age == 3 && MPI == 50)) {	// checking if it is dead
			cout << "- " << name << " is dead because of AGING!" << endl;
			is_alive = false;
		}
		if (is_alive && MP >= mutate_at) {	// checking mutation
			mutated_to = "Grayling3";
			MPI = 50;
			MP = 0;
			mutate_at = 100;
			is_mutant = true;
			cout << "- Mutated TO: " << mutated_to << endl;
		}
	}
	else
		cout << "- Trying to AGING BUT " << name << " is not alive" << endl;
}

Grayling3::Grayling3(char gender_in, string name_in) : Grayling(gender_in, name_in) {	// Constructor
	MPI = 50;
	MP = 0;
	mutate_at = 100;
}

Grayling3::Grayling3(const Grayling3 &obj_in, char gender, string name) : Grayling(obj_in, gender, name) {}	// Copy Constructor

void Grayling3::print() const {	// virtual function
	cout << "- Grayling 3 -> Age: " << age << " Name: " << name << " G: " << gender << " MPI: " << MPI << " MP: " << MP << " Mutate at: " << mutate_at << endl;
}

void Grayling3::givebirth() {	// virtual function
	if (is_alive) {
		if (gender == 'f' || gender == 'F') {
			cout << "- Trying to GIVE BIRTH BUT " << name << " has no ability to give birth. It caused the death of the grayling." << endl;
			is_alive = false;
		}
		else
			cout << "- Trying to GIVE BIRTH BUT " << name << " has no ability to give birth becuase of its gender." << endl;
	}
	else
		cout << "- Trying to GIVE BIRTH BUT " << name << " is not alive and has no ability to give birth!" << endl;
}

void Grayling3::aging() {	// virtual function
	if (is_alive) {
		age++;
		MP += MPI;
		cout << "- AGING: Name: " << name << " -> " << (is_mutant ? mutated_to : "") << " Age: " << age << " MPI: " << MPI << " MP: " << MP << endl;
		if (age == 3 && MPI == 50) {	// checking if it is dead
			cout << "- " << name << " is dead because of AGING!" << endl;
			is_alive = false;
		}
		if (MP >= mutate_at) {	// checking mutation
			cout << "- " << name << " is dead because of HIGH MUTATION RATE!" << endl;
			is_alive = false;
		}
	}
	else
		cout << "- Trying to AGING BUT " << name << " is not alive" << endl;
}
