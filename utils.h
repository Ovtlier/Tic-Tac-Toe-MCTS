// Author: Rodney Boyce

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define EMPTY_CELL -1

int scanInt();

bool validMove(int x, int y, int **b, int size);

void displayBoard(int **b);

bool isGameOver(int **b);

int isGameWon(int **b);

bool isBoardFull(int **b);

int **createBoard();

void setBoardEmpty(int **b);

void copyBoard(int **dest, int **src);

void freeBoard(int **b);

#endif