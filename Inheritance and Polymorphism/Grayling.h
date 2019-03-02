#ifndef GRAYLING_H
#define GRAYLING_H
#include <iostream>
#include <string>

using namespace std;

class Grayling {
protected:
	short age;
	string name;
	char gender;
	bool is_alive;
	bool is_mutant;
	string mutated_to;
	double MPI;
	double MP;
	double mutate_at;
public:
	Grayling();	// Default Constructor
	Grayling(char, string);	// Constructor
	Grayling(const Grayling &, char, string);	// Copy Constructor
	virtual void print() const;
	virtual void givebirth();
	virtual void aging();
};

class Grayling1 : public Grayling {
public:
	Grayling1(char, string);	// Constructor
	Grayling1(const Grayling1 &, char, string);	// Copy Constructor
	void print() const;
	void givebirth();
	void aging();
};

class Grayling2 : public Grayling {
public:
	Grayling2(char, string);	// Constructor
	Grayling2(const Grayling2 &, char, string);	// Copy Constructor
	void print() const;
	void givebirth();
	void aging();
};

class Grayling3 : public Grayling {
public:
	Grayling3(char, string);	// Constructor
	Grayling3(const Grayling3 &, char, string);	// Copy Constructor
	void print() const;
	void givebirth();
	void aging();
};
#endif