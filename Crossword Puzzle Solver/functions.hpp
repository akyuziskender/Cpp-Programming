#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// function prototypes
int number_of_lines(char const *filename);
string str_reverse(string word);

int number_of_lines(char const *filename) {
    // Initializing variables
    ifstream fPtr(filename);  // opening the file for reading
    int line_counter = 0;
    string line;
    while(getline(fPtr, line)) {
        if(line.length() > 0) line_counter++;
    }
    fPtr.close();  // closing the file
    return line_counter;  // returning number of lines in the file
}
// a function that returns reverse of a string
string str_reverse(string word) {
    int length = word.length();
    size_t i;
    string reverse;
    for(i = 0; i < length; i++) {
        reverse += word[length - i - 1];
    }
    return reverse;
}
