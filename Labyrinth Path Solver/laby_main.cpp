#include <iostream>
#include <stdio.h>
#include "laby_struct.h"

#define ROW 14
#define COLUMN 21

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

#define WALL '#'

using namespace std;
// the labyrinth that we are in
char lab[ROW][COLUMN + 1] = {"#o###################",
							 "#     #      #    # #",
							 "# ### # ###### ## # #",
							 "# # #        # #  # #",
						 	 "# # ### ######## ## #",
							 "#     # # ##   #    #",
							 "### # # # ## # # ####",
							 "# # # # #    #      #",
							 "# # # # # ######### #",
							 "# # # # # #       # #",
							 "# # #   # # #####   #",
							 "# # ##### # #   #####",
							 "#         #   #     #",
							 "###################E#"};
// function prototypes
void Initialization();
void PrintLab(char l[ROW][COLUMN + 1]);
void PrintFinalPath();
void Move();
void DeletePath(position);

Stack s, path, circle_points;
position entrance; 
position out, p;
bool goback = false;

int main() {
	s.create();	// create the stack which will hold the decision points
	path.create();	// create the stack which will hold the path to the exit
	circle_points.create();	// create the stack wich will hold the starting point of the circles

	Initialization();	// Before starting, initialize some variables
	
	PrintLab(lab);	// Print the labyrinth to the console

	while (p.x != out.x || p.y != out.y) {
		Move();
	}

	lab[p.y][p.x] = 'o';
	path.push(p);
	PrintLab(lab);  // After finding the out, print the labyrinth with the path

	cout << "PATH found!" << endl << endl;
	PrintFinalPath();	// Printing the path we came through to the console
	getchar();

	s.close();
	path.close();
	circle_points.close();

	return 0;
}

void Initialization() {
	entrance = { 1, 0, 0, 0, 0, 0, 0 };	// the entrance point
	out = { 19, 13, 0, 0, 0, 0, 0 };	// the exit point where we will be free
	p = entrance;	// the current point. at first, we are at the entrance
	p.camefrom = UP;	// we are entering the labyrinth from UP
	return;
}

void PrintLab(char l[ROW][COLUMN + 1]) {
	system("cls");	// clear the screen
	for (int i = 0; i < ROW; i++) {
		cout << " ";
		for (int j = 0; j < COLUMN + 1; j++) {
			cout << l[i][j];
		}
		cout << endl;
	}
	getchar();
	return;
}

void PrintFinalPath() {
	position temp;
	while (!path.isempty()) {
		temp = path.pop();
		cout << "X: " << temp.x << "\tY: " << temp.y << endl;
	}
}

void Move() {
	position temp_current_p;
	lab[p.y][p.x] = 'o';
	PrintLab(lab);
	// first find in how many directions we can move
	if (!goback) {	// if not calculated before
		p.right = 0; p.left = 0; p.down = 0; p.up = 0;
		if (p.x < COLUMN - 1 && lab[p.y][p.x + 1] != WALL) p.right = 1;	// right
		if (p.x > 0 && lab[p.y][p.x - 1] != WALL) p.left = 1;	// left
		if (p.y < ROW - 1 && lab[p.y + 1][p.x] != WALL) p.down = 1;	// down
		if (p.y > 0 && lab[p.y - 1][p.x] != WALL) p.up = 1;	// up
	}
	else goback = false;

	//here, one of the possible moves is selected
	bool moved = true;
	position past = p;
	if (p.down && p.camefrom != DOWN) {
		p.y++; p.camefrom = UP; past.down = 0;
	}
	else if (p.up && p.camefrom != UP) {
		p.y--; p.camefrom = DOWN; past.up = 0;
	}
	else if (p.left && p.camefrom != LEFT) {
		p.x--; p.camefrom = RIGHT; past.left = 0;
	}
	else if (p.right && p.camefrom != RIGHT) {
		p.x++; p.camefrom = LEFT; past.right = 0;
	}
	else moved = false;	// one direction is open, but this is the direction we came from

	if (p.x != out.x || p.y != out.y) {
		if ((p.down + p.up + p.right + p.left) > 2) {
			/* there is more than one choice, push onto stack and continue in that
			   chosen direction. Let the choices you have not selected remain marked
			   on the stack */
			s.push(past);
		}
	}
	position temp1, temp2;
	if(moved) path.push(past);

	if (!moved || lab[p.y][p.x] == 'o') {	// has to go back
		if (!s.isempty()) {
			// checking if we encounter with 'o', that means we are in a circle
			if (lab[p.y][p.x] == 'o') {
				circle_points.push(p);
				p = past;
				temp1 = circle_points.top();
				temp2 = s.top();
				/* if the decision point and the circle starting point is equal,
				   then go back to the previous decision point */
				if (temp1.x == temp2.x && temp1.y == temp2.y)
					s.pop();
			}
			
			temp_current_p = p;
			p = s.pop();
			/* Since we are turning back to the decision point,
			   we need to delete the path we came till the decision point */
			DeletePath(temp_current_p);
			goback = true;
		}
	}
	return;
}

void DeletePath(position temp_current_p) {
	position temp = path.pop();
	lab[temp_current_p.y][temp_current_p.x] = ' ';
	PrintLab(lab);

	while (temp.x != p.x || temp.y != p.y) {
		lab[temp.y][temp.x] = ' ';
		PrintLab(lab);
		temp = path.pop();
	}
	return;
}