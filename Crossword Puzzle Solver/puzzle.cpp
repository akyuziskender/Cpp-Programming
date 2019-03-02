/* @Author
* Student Name: İskender Akyüz
* Student ID : 150150150
* Date: 10.09.2017
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctype.h>
#include <cstring>
#include <string>
#include "functions.hpp"

using namespace std;

struct searchedWord{
    int id;  // it holds priortiy of the word
    char *word;  // it holds the word
    int wordLength;  // the length of the word
};

bool check = false;
char **puzzleArray_temp = new char*[15];  // a global temp array where the words will be deleted
// function prototypes
void delete_puzzle(int, int, int, int, int);
void operations_on_found_word(string word, int row, int column, string direction);
bool horizontalSearch(char** puzzleArray, searchedWord* word);
bool verticalSearch(char** puzzleArray, searchedWord* word);
bool diagonalSearch(char** puzzleArray, searchedWord* word);

int main() {
    // Initializing variables
    int a;
    char **puzzleArray = new char*[15];  // taking space in memory to form 2-D array
    for(a = 0; a < 15; a++) {
        puzzleArray[a] = new char[15];
    }
    for(a = 0; a < 15; a++) {
        puzzleArray_temp[a] = new char[15];
    }

    FILE *puzzle_file, *words_file;
    ofstream last_puzzle;

    int i = 0, j = 0;
    char letter;
    char word[16];
    int ID, read_counter, number_of_words;
    char buff[255];

    puzzle_file = fopen("puzzle.txt", "r");  // opening the file for reading
    while(!feof(puzzle_file)) {
        fread(&letter, sizeof(char), 1, puzzle_file);  // reading a character from the file
        if(feof(puzzle_file)) break;
        if(isalpha(letter)) {  // checking if character is an alphabetic letter
            *(*(puzzleArray+i)+j) = letter;  // adding the letter to a 2D matrix
            *(*(puzzleArray_temp+i)+j) = letter;
            j++;  // incrementing j to pass to next column
            if(j == 15) {  // checking if we finish the line
                j = 0;  // passing to first column again
                i++;  // passing to next line by incrementing i
            }
            if (i == 15) break;  // checking if we fill the whole matrix
        }
    }
    fclose(puzzle_file);  // closing the file

    number_of_words = number_of_lines("searchedwords.txt");  // calculating the number of words in the file
    searchedWord words_list[number_of_words];  // creating an struct array whose size equals to number of words, so we use exactly the space we need

    words_file = fopen("searchedwords.txt", "r");  // opening the file for reading
    i = 0;
    while(fgets(buff, sizeof(buff), words_file)) {
        read_counter = sscanf(buff, "%d %s", &ID, word);  // reading the word and its id
        if(read_counter != 2) break;
        (words_list+i)->word = new char[strlen(word) + 1]; // getting space in memory for word
        (words_list+i)->id = ID;  // assigning id to its struct
        strcpy((words_list+i)->word, word);  // copying word into the struct
        (words_list+i)->wordLength = strlen(word);  // assigning word's length
        i++;
    }
    fclose(words_file);  // closing the file

    bool *searched = new bool[number_of_words];  // creating an array for sorting
    for(a = 0; a < number_of_words; a++) *(searched+a) = false; // assigning all index to false

    int min_index;
    for(i = 0; i < number_of_words; i++) {
        min_index = 0;
        while(searched[min_index])
            min_index++;
        for(j = 0; j < number_of_words; j++) {
            if(!searched[j] && ((words_list+j)->id < (words_list+min_index)->id)) {
                min_index = j;
            }
        }
        *(searched+min_index) = true;  // to indicate that word is searched, assigning its index to true
        if(verticalSearch(puzzleArray, words_list + min_index)) continue;  // doing horizontal search
        if(horizontalSearch(puzzleArray, words_list + min_index)) continue;  // doing vertical search
        if(diagonalSearch(puzzleArray, words_list + min_index)) continue;  // doing diagonal search
    }

    last_puzzle.open("lastVersionPuzzle.txt");  // opening the file for writing
    for(i = 0; i < 15; i++) {
        if(i != 0) last_puzzle << "\n";
        for(j = 0; j < 15; j++) {
            last_puzzle << *(*(puzzleArray_temp+i)+j) << " ";  // writing the last version of puzzle into file
        }
    }
    last_puzzle.close();  // closing file

    for(a = 0; a < number_of_words; a++) {
        delete[] (words_list+a)->word;  // deleting memory
    }

    for(a = 0; a < 15; a ++) {
        delete[] *(puzzleArray+a);  // deleting memory
    }
    delete[] puzzleArray;  // deleting memory

    for(a = 0; a < 15; a ++) {
        delete[] *(puzzleArray_temp+a);  // deleting memory
    }
    delete[] puzzleArray_temp;  // deleting memory
    delete[] searched;  // deleting memory
    return 0;
}

void delete_puzzle(int row_start, int column_start, int row_end, int column_end, int var) {
    int i, j;
    // There are three cases
    if(var == 1) {    // 1) for horizontal and vertical search, we need to increment i and j seperately
        for(i = row_start; i <= row_end; i++) {
            for(j = column_start; j <= column_end; j++) {
                *(*(puzzleArray_temp+i)+j) = ' ';  // making empty that index
            }
        }
        return;
    }
    else if(var == 2){  // 2) for diagonal search (top-left to bottom-right and vice versa), we need to increment i and j at the same time in the 2nd for loop
        for(i = row_start; i <= row_end; i++) {
            for(j = column_start; j <= column_end; j++, i++) {
                *(*(puzzleArray_temp+i)+j) = ' ';  // making empty that index
            }
        }
        return;
    }
    else if(var == 3){  // 3) for diagonal search (top-right to bottom-left and vice versa), we need to increment i, and decrement j in the 2nd for loop
        for(i = row_start; i <= row_end; i++) {
            for(j = column_start; j >= column_end; j--, i++) {
                *(*(puzzleArray_temp+i)+j) = ' ';  // making empty that index
            }
        }
        return;
    }
}

void operations_on_found_word(string word, int row, int column, int direction) {
    // Initializing variables
    FILE *foundWords;
    char text[50], temp_word[16];
    strcpy(temp_word, word.c_str());  // converting string to char[]

    switch(direction) {
        case 1: // Horizontal - Right to Left
            sprintf(text, "%s\t%s\t[%d][%d] - [%d][%d]", temp_word, "HORIZONTAL", row, column, row, column + (int)word.length() - 1);
            delete_puzzle(row, column, row, column + (int)word.length() - 1, 1);  // calling delete function for the word
            break;
        case 2: // Horizontal - Left to Right
            sprintf(text, "%s\t%s\t[%d][%d] - [%d][%d]", temp_word, "HORIZONTAL", row, column, row, column - (int)word.length() + 1);
            delete_puzzle(row, column - (int)word.length() + 1, row, column, 1);  // calling delete function for the word
            break;
        case 3: // Vertical - Up to Down
            sprintf(text, "%s\t%s\t[%d][%d] - [%d][%d]", temp_word, "VERTICAL", row, column, row + (int)word.length() - 1, column);
            delete_puzzle(row, column, row + (int)word.length() - 1, column, 1);  // calling delete function for the word
            break;
        case 4: // Vertical - Down to Up
            sprintf(text, "%s\t%s\t[%d][%d] - [%d][%d]", temp_word, "VERTICAL", row, column, row - (int)word.length() + 1, column);
            delete_puzzle(row - (int)word.length() + 1, column, row, column, 1);  // calling delete function for the word
            break;
        case 5: // Diagonal - Top-left to Bottom-right
            sprintf(text, "%s\t%s\t[%d][%d] - [%d][%d]", temp_word, "DIAGONAL", row, column, row + (int)word.length() - 1, column + (int)word.length() - 1);
            delete_puzzle(row, column, row + (int)word.length() - 1, column + (int)word.length() - 1, 2);  // calling delete function for the word
            break;
        case 6: // Diagonal - Bottom-right to Top-left
            sprintf(text, "%s\t%s\t[%d][%d] - [%d][%d]", temp_word, "DIAGONAL", row, column, row - (int)word.length() + 1, column - (int)word.length() + 1);
            delete_puzzle(row - (int)word.length() + 1, column - (int)word.length() + 1, row, column, 2);  // calling delete function for the word
            break;
        case 7: // Diagonal - Top-right to Bottom-left
            sprintf(text, "%s\t%s\t[%d][%d] - [%d][%d]", temp_word, "DIAGONAL", row, column, row + (int)word.length() - 1, column - (int)word.length() + 1);
            delete_puzzle(row, column, row + (int)word.length() - 1, column - (int)word.length() + 1, 3);  // calling delete function for the word
            break;
        case 8: // Diagonal - Bottom-left to Top-right
            sprintf(text, "%s\t%s\t[%d][%d] - [%d][%d]", temp_word, "DIAGONAL", row, column, row - (int)word.length() + 1, column + (int)word.length() - 1);
            delete_puzzle(row - (int)word.length() + 1, column + (int)word.length() - 1, row, column, 3);  // calling delete function for the word
            break;
    }
    if(!check) {
        foundWords = fopen("foundWordsInfo.txt", "w");  // opening a file for writing
        check = true;  // indicates that the file was created and its 1st line was written.
        fprintf(foundWords, "%s", text);  // writing the found word into the file
        fclose(foundWords);  // closing the file
    }
    else {
        foundWords = fopen("foundWordsInfo.txt", "a");  // opening the file for appending
        fprintf(foundWords, "\n%s", text);  // writing the found word into the file
        fclose(foundWords);  // closing the file
    }
    return;
}

bool horizontalSearch(char** puzzleArray, searchedWord* word) {
    // Initializing variables
    size_t i, j;
    string temp, temp_reverse;
    // searching from right to left and vice versa
    for(i = 0; i < 15; i++) {
        for(j = 0; j < 15; j++) {
            temp += *(*(puzzleArray+i)+j);  // adding the characters in the row to form a string
        }
        temp += '\0';
        if(temp.find(word->word) != string::npos) {  // searching the word in the string created by characters of the column
            operations_on_found_word(word->word, i, temp.find(word->word), 1);
            return true;  // If it is found, return true
        }
        temp_reverse = str_reverse(temp);  // reversing the horizontal line
        if(temp_reverse.find(word->word) != string::npos) {
            operations_on_found_word(word->word, i, 15 - temp_reverse.find(word->word), 2);
            return true;
        }
        temp = "";  // making empty the string in order to use it again
    }
    return false;  // If it is not found, return false
}

bool verticalSearch(char** puzzleArray, searchedWord* word) {
    // Initializing variables
    size_t i, j;
    string temp, temp_reverse;
    // searching from up to down and vice versa
    for(j = 0; j < 15; j++) {
        for(i = 0; i < 15; i++) {
            temp += *(*(puzzleArray+i)+j);  // adding the characters in the column to form a string
        }
        temp += '\0';
        if(temp.find(word->word) != string::npos) {  // searching the word in the string created by characters of the column
            operations_on_found_word(word->word, temp.find(word->word), j, 3);
            return true;  // If it is found, return true
        }
        temp_reverse = str_reverse(temp);  // reversing the vertical line
        if(temp_reverse.find(word->word) != string::npos) {  // searcing the reversed
            operations_on_found_word(word->word, 15 - temp_reverse.find(word->word), j, 4);
            return true;
        }
        temp = "";  // making empty the string in order to use it again
    }
    return false;  // If it is not found, return false
}

bool diagonalSearch(char** puzzleArray, searchedWord* word) {
    // Initializing variables
    size_t i, j, temp_i, temp_j = 0;
    string temp, temp_reverse;
    bool flag = true;
    // searching from top-left to bottom-right and vice versa
    for(i = 0; i < 15; i++) {
        if(flag) temp_i = i;  // to detect whether the lower triangular is finished, there is an if statement here
        for(j = temp_j; j < 15; i++, j++) {
            if(i == 15 || j == 15) break;
            temp += *(*(puzzleArray+i)+j);  // adding the characters in the column to form a string
        }
        i = temp_i;
        temp += '\0';
        if(temp.find(word->word) != string::npos) {  // searching the word in the string created by characters of the column
            if(flag) {
                operations_on_found_word(word->word, temp.find(word->word) + i, temp.find(word->word), 5);
            }
            else {
                operations_on_found_word(word->word, temp.find(word->word), temp_j + temp.find(word->word), 5);
            }
            return true;  // If it is found, return true
        }
        temp_reverse = str_reverse(temp);  // reversing the string
        if(temp_reverse.find(word->word) != string::npos) {
            if(flag) {
                operations_on_found_word(word->word, 15 - temp_reverse.find(word->word), j - temp_reverse.find(word->word), 6);
            }
            else {
                operations_on_found_word(word->word, 15 - temp_reverse.find(word->word) - temp_j, 15 - temp_reverse.find(word->word), 6);
            }
            return true;
        }
        temp = "";  // making empty the string in order to use it again
        if(temp_i == 14 && temp_j == 15) break;  // break if the puzzle is completely read
        if(i >= 14) {  // after reading lower triangular, the upper triangular will be read. in order to that, we need to make some changes
            i = -1;  // returning the first row again
            temp_j++;
            flag = false;  // indicating that we are done with the lower triangular
        }
    }
    flag = true;
    temp_j = 0;

    // searching from top-right to bottom-left and vice versa
    for(i = 0; i < 15; i++) {
        if(flag) temp_i = i;
        for(j = temp_j; j < 15; i++, j++) {
            if(i == 15 || j == 15) break;
            temp += *(*(puzzleArray+(i))+(14-j));  // adding the characters in the column to form a string
        }
        i = temp_i;
        temp += '\0';
        if(temp.find(word->word) != string::npos) {  // searching the word in the string created by characters of the column
            if(flag) {
                operations_on_found_word(word->word, i + temp.find(word->word), 15 - temp.find(word->word) - 1, 7);
            }
            else {
                operations_on_found_word(word->word, temp.find(word->word), 15 - temp.find(word->word) - temp_j - 1, 7);
            }
            return true;  // If it is found, return true
        }
        temp_reverse = str_reverse(temp);
        if(temp_reverse.find(word->word) != string::npos) {
            if(flag) {
                operations_on_found_word(word->word, 15 - temp_reverse.find(word->word), 15 - j + temp_reverse.find(word->word) - 1, 8);
            }
            else {
                operations_on_found_word(word->word, 15 - temp_reverse.find(word->word) - temp_j, temp_reverse.find(word->word) - 1, 8);
            }
            return true;
        }
        temp = "";  // making empty the string in order to use it again
        if(temp_i == 14 && temp_j == 15) break;  // break if the puzzle is completely read
        if(i >= 14) {  // after reading lower triangular, the upper triangular will be read. in order to that, we need to make some changes
            i = -1;  // returning the first row again
            temp_j++;
            flag = false;  // indicating that we are done with the lower triangular
        }
    }
    return false;
}

// 00111100 01001101 01000101 0011011
// by marnop
