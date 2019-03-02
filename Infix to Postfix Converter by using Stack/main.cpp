// main.cpp
// Testing the operations that we can perform on the stack

#include <iostream> // allows program to perform input and output
#include <stdlib.h>
#include <iomanip>
#include <string>

#include <ctype.h>

#include "stack_1.h" // include implementation of struct Stack

using namespace std; // enables the program to use all the names in any included standard C++ header

int do_math(char a, char b, char op);
int precedence(char);
bool comparePrecedence(char, char);

// function main begins program execution
int main()
{
	Stack operators, postfixform, temp_stack;
	operators.create();
	postfixform.create();
	temp_stack.create();
	string input, postfix;
	int i, n, result = 0;
	char c, temp, first, second;
	bool flag = false;

	cout << "Enter an infix operation:" << endl;
	getline(cin, input);
	n = input.length();

	for(i = 0; i < n; i++) {
		c = input[i];
		if(isdigit(c)) {
			postfix += c;
			postfixform.push(c);
		}
		else {
			if(c == ')') {
				do{
					temp = operators.pop();
					if(temp == '(') break;
					postfix += temp;
					postfixform.push(temp);
				}while(temp != '(');
			}
			else if(operators.isempty() || c == '(')
				operators.push(c);
			else if(!operators.isempty()) {
				do {
					if(comparePrecedence(operators.top(), c)) {
						flag == true;
						temp = operators.pop();
						postfix += temp;
						postfixform.push(temp);
						operators.push(c);
					}
					else {
						flag = false;
						operators.push(c);
					}
				}while(!operators.isempty() && flag);
			}
		}
	}
	while(!operators.isempty()) {
		temp = operators.pop();
		postfix += temp;
		postfixform.push(temp);
	}


	while(!postfixform.isempty()) {
		temp = postfixform.pop();
		cout << temp << endl;
		if(!isdigit(temp)) {
			temp_stack.push(temp);
		}
		else{
			first = temp;
			second = postfixform.pop();
			cout << second << " " << temp_stack.top() << " " << first << endl;
			result += do_math(second, first, temp_stack.pop());
			postfixform.push(result+48);
			cout << "result: " << result << endl;
			while(!temp_stack.isempty()) {
				postfixform.push(temp_stack.pop());
			}
		}
	}

	cout << "\nPostfix expression: " << postfix << "\t\t" << result << endl;
	operators.close();
	postfixform.close();
	temp_stack.close();

	return EXIT_SUCCESS; // C++ macro that indicates program was executed successfully
}

int do_math(char a, char b, char op) {
	int first = (int)a - 48;
	int second = (int)b - 48;
	cout << "HH" << first << second << endl;
	switch(op) {
		case '*':
			return first*second;
		case '/':
			return first/second;
		case '+':
			return first+second;
		case '-':
			return first-second;
	}
}

int precedence(char op) {
	if(op == '*' || op == '/') return 1;
	return 0;
}

bool comparePrecedence(char a, char b) {
	return precedence(a) > precedence(b);
}
