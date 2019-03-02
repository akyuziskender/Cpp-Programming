#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

bool sudokuChecker(int sudoku[9][9]);

int main() {
	int sudoku_array[9][9] = { 0 };
	FILE *sudoku_file;
	char file_name[15];
	char *file = "sudoku";
	char *ext = ".txt";
	char number;
	int num;
	int i = 0, j = 0, k;

	for (k = 0; k < 3; k++) {
		sprintf(file_name, "%s%d%s", file, k + 1, ext);
		sudoku_file = fopen(file_name, "r");
		while (!feof(sudoku_file)) {
			fread(&number, sizeof(char), 2, sudoku_file);
			num = number - 48;
			if (num >= 1 && num <= 9) sudoku_array[i][j] = num;
			else sudoku_array[i][j] = 0;
			if (i == 9) i = 0;
			if (j == 9) {
				j = 0;
				i++;
			}
			j++;
		}
		fclose(sudoku_file);

		if (sudokuChecker(sudoku_array)) cout << "The sudoku #" << k+1 << " is VALID." << endl;
		else cout << "The sudoku #" << k+1 << " is INVALID." << endl;
	}
	return 0;
}

bool sudokuChecker(int sudoku[9][9]) {
	int temp[10] = { 0 };
	bool flag = false;
	int i, j, k;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (temp[sudoku[i][j]] == 1 || sudoku[i][j] == 0) {
				flag = true;
				break;
			}
			else {
				temp[sudoku[i][j]] = 1;
			}
		}
		if (flag) break;
		for (k = 0; k < 10; k++) temp[k] = 0;
	}

		if (flag) return false;
		else return true;
}