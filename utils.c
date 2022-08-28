// Author: Rodney Boyce

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

static bool inBounds(int x, int y, int size);
static void clearStdin();

int scanInt() {
    int intValue;
    char nLine;
    while (scanf("%d%c", &intValue, &nLine) != 2 || nLine != '\n') {
        fprintf(stderr, "Invalid input, please try again.\n");
        clearStdin();
    }
    return intValue;
}

static void clearStdin() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        continue;
    }
}

bool validMove(int x, int y, int **b, int size) {
    if (inBounds(x, y, size)) {
        if (b[y][x] == EMPTY_CELL) {
            return true;
        }
    }
    return false;
}

static bool inBounds(int x, int y, int size) {
    if ((0 <= x && x < size) && (0 <= y && y < size)) {
        return true;
    }
    return false;
}

void displayBoard(int **b) {
    printf("-------------\n");
    for (int i = 0; i < 3; i++) {
        char leftC = ' ';
        char centerC = ' ';
        char rightC= ' ';
        if (b[i][0] != EMPTY_CELL) {
            leftC = (b[i][0] == 1) ? 'X': 'O';
        }
        if (b[i][1] != EMPTY_CELL) {
            centerC = (b[i][1] == 1) ? 'X': 'O';
        }
        if (b[i][2] != EMPTY_CELL) {
            rightC = (b[i][2] == 1) ? 'X': 'O';
        }
        printf("| %c | %c | %c |\n", leftC, centerC, rightC);
        printf("-------------\n");
    }
}

bool isGameOver(int **b) {
    if (isGameWon(b) != -1) {
        return true;
    }
    return isBoardFull(b);
}

int isGameWon(int **b) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if ((b[i][0] == b[i][1] && b[i][1] == b[i][2]) && b[i][0] != EMPTY_CELL) {
            return b[i][0];
        }
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        if ((b[0][i] == b[1][i] && b[1][i] == b[2][i]) && b[0][i] != EMPTY_CELL) {
            return b[0][i];
        }
    }
    // Check diagonals
    if ((b[0][0] == b[1][1] && b[1][1] == b[2][2]) && b[1][1] != EMPTY_CELL) {
        return b[1][1];
    }
    if ((b[0][2] == b[1][1] && b[1][1] == b[2][0]) && b[1][1] != EMPTY_CELL) {
        return b[1][1];
    }

    return -1;
}

bool isBoardFull(int **b) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == EMPTY_CELL) {
                return false;
            }
        }
    }
    return true;
}

int **createBoard() {
    int **newB = malloc(sizeof(int*) * 3);
    for (int i = 0; i < 3; i++) {
        newB[i] = malloc(sizeof(int) * 3);
    }
    return newB;
}

void setBoardEmpty(int **b) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            b[i][j] = EMPTY_CELL;
        }
    }
}

void copyBoard(int **dest, int **src) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

void freeBoard(int **b) {
    for (int i = 0; i < 3; i++) {
        free(b[i]);
    }
    free(b);
}