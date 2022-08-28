// Author: Rodney Boyce

#include "player.h"

#include "mctsAI.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

#define P_NOUGHT 0
#define P_CROSS 1

static void makeMove(Player self);
static void humanMove(Player p);
static void mctsMove(Player p);

Player createPlayer(int isH, int pT, int **b, int sz) {
    Player newP = malloc(sizeof(*newP));
    if (newP == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    newP->isHuman = isH;
    newP->pType = pT;
    newP->board = b;
    newP->bSize = sz;
    newP->xMove = -1;
    newP->yMove = -1;
    newP->makeMove = &makeMove;
    return newP;
}

static void makeMove(Player self) {
    if (self->isHuman) {
        humanMove(self);
        while (!validMove(self->xMove, self->yMove, self->board, self->bSize)) {
            printf("Invalid move!\n");
            humanMove(self);
        }
    } else {
        mctsMove(self);
    }
}

static void humanMove(Player p) {
    int x, y;
    printf("\tX Co-ordinate: ");
    p->xMove = scanInt();
    printf("\tY Co-ordinate: ");
    p->yMove = scanInt();
    p->xMove--;
    p->yMove--;
}

static void mctsMove(Player p) {
    int mctsMove = doMCTS(p->board, p->pType);
    p->yMove = mctsMove / 3;
    p->xMove = mctsMove % 3;
}