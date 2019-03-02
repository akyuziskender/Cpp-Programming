#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>

using namespace std;

template <class Type>
class genericArray{
private:
	int size;
public:
	Type *elements;
	Type total;
public:
	genericArray(int);	// Constructor
	~genericArray();	// Destructor
	Type sum();
};

template<class Type>
genericArray<Type>::genericArray(int insize) {
	if (insize < 0)
		throw "The size cannot be a negative number!";
	size = insize;
	elements = new Type[size];	// allocating memory
}

template<class Type>
genericArray<Type>::~genericArray() {	// Destructor
		delete[] elements;	// delete memory
}

template<class Type>
Type genericArray<Type>::sum() {
	total = 0;
	for (int i = 0; i < size; i++)
		total += *(elements + i);
	return total;
}

class Money {
private:
	int lira;
	int kurus;
public:
	Money();	// Default Constructor
	Money(int, int);	// Constructor
	// Operator overloading
	bool operator < (int);
	bool operator > (int);
	Money & operator =(Money const &obj);
	Money & operator =(int);
	Money & operator += (Money const &obj);
	Money & operator -= (Money const &obj);
	friend std::ostream& operator<<(std::ostream&, const Money&);
};
#endif