/*header file for main.cpp*/
#include <iostream>
#include <iomanip> 
using namespace std;

class Gameboard
{
    char gameSpace[4][4];
public:
    Gameboard(); //initialize the board with '-' in all 16 spaces
    void setGameSpace(int row,int column, char value); //x,y,or '-' in each game square
    char getGameSpace(int row,int column);
    int fourInRow(char value); //four 'x's in any row 'wins'
    void printInfo(); //print the game board in a 4x4 matrix
};

Gameboard::Gameboard() {
    int i, j;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            gameSpace[i][j] = '_';
        }
    }
}

void Gameboard::setGameSpace(int row, int column, char value) {
    gameSpace[row][column] = value;
}

char Gameboard::getGameSpace(int row, int column) {
    return gameSpace[row][column];
}

int Gameboard::fourInRow(char value) {
    int i, j;
    bool flag = false;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(gameSpace[i][j] == value) flag = true;
            else {
                flag = false;
                break;
            }
        }
        if(flag) {
            return 1;
        }
    }
    return 0;
}

void Gameboard::printInfo() {
    int i, j;
    cout << endl;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            cout << "|" << gameSpace[i][j];
        }
        cout << "|\n";
    }
    cout << endl;
}

//TODO: complete the class definition