// Author: Rodney Boyce

#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

typedef struct player *Player;
struct player {
    /* 
    *************************************
    PRIVATE MEMBER: DO NOT ALTER 
    *************************************
    */
    bool isHuman;
    /* 
    *************************************
    PRIVATE MEMBER: DO NOT ALTER 
    *************************************
    */
    int pType;

    int **board;
    int bSize;
    int xMove;
    int yMove;

    void (*makeMove)(Player self);
};

Player createPlayer(int isH, int pT, int **b, int sz);

#endif