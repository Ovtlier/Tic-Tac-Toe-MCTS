// Author: Rodney Boyce

#ifndef TTT_H
#define TTT_H

#include <stdbool.h>

int getGameSetting();

int getPlayerSetting();

int **createBoard();

bool isGameOver(int **b);

int isGameWon(int **b);

bool isBoardFull(int **b);

#endif