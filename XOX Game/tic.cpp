#include "mainClasses.hpp"
#include <string>

int main() {
    Gameboard game;
    string userX, userY;
    int row, column, turns = 8;
    char choice;
    bool flag = false;
    
    cout << "First user's name: ";
    cin >> userX;
    cout << "Second user's name: ";
    cin >> userY;
    
    for(int i = 0; i < turns; i++) {
        // UserX's turn
        cout << userX << ", where do you want to put your 'x'? Which row and column? ";
        do {
            cin >> row;
            cin >> column;
            if(game.getGameSpace(row, column) == '_') {
                game.setGameSpace(row, column, 'x');
                break;
            }
            else {
                cout << "This index is taken. Please choose another one." << endl;
            }
        }while(1);
        if(game.fourInRow('x')) {
            cout << userX << " has won. Congratulations!\n" << endl;
            game.printInfo();
            flag = true;
            break;
        }
        game.printInfo();
        
        // UserY's turn
        cout << userY << ", where do you want to put your 'o'? Which row and column? ";
        do {
            cin >> row;
            cin >> column;
            if(game.getGameSpace(row, column) == '_') {
                game.setGameSpace(row, column, 'o');
                break;
            }
            else {
                cout << "This index is taken. Please choose another one." << endl;
            }
        }while(1);
        if(game.fourInRow('o')) {
            cout << userY << " has won. Congratulations!\n" << endl;
            game.printInfo();
            flag = true;
            break;
        }
        game.printInfo();
    }
    if(!flag) cout << "Tie game.\n" << endl;
    return 0;
    
}