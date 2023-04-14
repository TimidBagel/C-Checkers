#include <stdio.h>

char board[8][8];

void initBoard();
void printBoard();

int main() {
	initBoard();
	printBoard();

	char line[100];
	scanf_s(" % [^ \n]", line);
	printf(" % s\n", line);
	return 0;
}

void initBoard() {
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (row < 1) { board[row][col] = (col % 2 == 0) ? ' ' : 'O'; }
			else if (row < 2) { board[row][col] = (col % 2 == 1) ? ' ' : 'O'; }
			else if (row > 6) { board[row][col] = (col % 2 == 1) ? ' ' : 'X'; }
			else if (row > 5) { board[row][col] = (col % 2 == 0) ? ' ' : 'X'; }
		}
	}
}

void printBoard() {
	int i, row, col;
	for (i = 0; i < 33; i++) { printf("-"); }
	printf("\n");
	for (row = 0; row < 8; row++) {
		printf("| ");
		for (col = 0; col < 8; col++) {
			printf("%c | ", board[row][col]);
		}
		printf("\n");
		for (i = 0; i < 33; i++) { printf("-"); }
		printf("\n");
	}
}