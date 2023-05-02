#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char board[8][8];
char colchars[8] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };

void initBoard();
void printBoard();
int findIndex(char col);
void playerMove(char mark);
int checkWin(char mark);

int main() {
    printf("Welcome to Checkers!\n");
    initBoard();
    char mark = 'O';
    while (checkWin(mark) == 0){
        mark = (mark == 'X') ? 'O' : 'X';
        playerMove(mark);
        system("cls");
    }
    if (mark == 'X') {
        printf("Player O Won!\n");
    }
    else if (mark == 'O') {
        printf("Player X Won!\n");
    }
    return 0;
}

int checkWin(char mark) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (board[row][col] == mark) { return 0; }
        }
    }
    return 1;
}

void playerMove(char mark) {
    printBoard();

    int row, rowTarget;
    char col, colTarget;

    while (1) {
        printf("Player %c's move.\n", mark);
        printf("\nEnter a row and column to select a piece (eg. \'1A\'): ");
        scanf_s("%d %c", &row, &col);
        col = findIndex(toupper(col));
        row--;

        if (board[row][col] != mark) {
            printf("\nRow and column must reference a square controlled by you!\n");
            continue;
        }

        printf("\nEnter a row and column to select an empty square: ");
        scanf_s("%d %c", &rowTarget, &colTarget);
        colTarget = findIndex(toupper(colTarget));
        rowTarget--;

        if (board[rowTarget][colTarget] == 'X' ||
            board[rowTarget][colTarget] == 'O') {
            printf("\nCannot choose already occupied space!\n");
            continue;
        }

        else if ((mark == 'X' &&
            (rowTarget == row - 2 &&
                (colTarget == col - 2 && board[row - 1][col - 1] == 'O') ||
                (colTarget == col + 2 && board[row - 1][col + 1] == 'O'))) ||
            (mark == 'O' &&
                (rowTarget == row + 2 &&
                    (colTarget == col - 2 && board[row + 1][col - 1] == 'X') ||
                    (colTarget == col + 2 && board[row + 1][col + 1] == 'X')))) {
            if (mark == 'X') {
                if (colTarget > col) {
                    board[row - 1][col + 1] = ' ';
                }
                else {
                    board[row - 1][col - 1] = ' ';
                }
            }
            else {
                if (colTarget > col) {
                    board[row + 1][col + 1] = ' ';
                }
                else {
                    board[row + 1][col - 1] = ' ';
                }
            }
            break;
        }

        else if (mark == 'X' && (rowTarget == row - 1 &&
            (colTarget == col + 1 || colTarget == col - 1))) {
            break;
        }

        else if (mark == 'O' && (rowTarget == row + 1 &&
            (colTarget == col + 1 || colTarget == col - 1))) {
            break;
        }

        else {
            printf("\nSpace must be a legal move!\n");
            continue;
        }
    }

    board[row][col] = ' ';
    board[rowTarget][colTarget] = mark;
}

void initBoard() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (row < 1) {
                board[row][col] = (col % 2 == 1) ? ' ' : 'O';
            }
            else if (row < 2) {
                board[row][col] = (col % 2 == 0) ? ' ' : 'O';
            }
            else if (row > 6) {
                board[row][col] = (col % 2 == 0) ? ' ' : 'X';
            }
            else if (row > 5) {
                board[row][col] = (col % 2 == 1) ? ' ' : 'X';
            }
            else {
                board[row][col] = ' ';
            }
        }
    }
}

void printBoard() {
    int i, row, col;
    printf("  ");
    for (i = 0; i < 33; i++) {
        printf("-");
    }
    printf("\n");
    for (row = 0; row < 8; row++) {
        printf("%d | ", row + 1);
        for (col = 0; col < 8; col++) {
            printf("%c | ", board[row][col]);
        }
        printf("\n");
        printf("  ");
        for (i = 0; i < 33; i++) {
            printf("-");
        }
        printf("\n");
    }
    printf("   ");
    for (col = 0; col < 8; col++) {
        printf(" %c  ", colchars[col]);
    }

    printf("\n");
}

int findIndex(char col) {
    int index = 0;
    while (index < sizeof(colchars) && colchars[index] != col) {
        index++;
    }
    return index;
}