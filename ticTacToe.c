// Author: Rodney Boyce

#include "ticTacToe.h"
#include "player.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SETTING_PVP 1
#define SETTING_PVE 2
#define P_NOUGHT 0
#define P_CROSS 1

int main(void) {
    srand(time(NULL));
    Player crossP;
    Player noughtP;
    int **gameBoard = NULL;
    int winningP;
    int gSetting = 0;
    int pSetting = 0;
    int playerTurn = 1;

    printf("TicTacToe MCTS!\n");

    gameBoard = createBoard();
    setBoardEmpty(gameBoard);

    gSetting = getGameSetting();
    if (gSetting == SETTING_PVE) {
        pSetting = getPlayerSetting();
        if (pSetting == P_CROSS) {
            crossP = createPlayer(1, P_CROSS, gameBoard, 3);
            noughtP = createPlayer(0, P_NOUGHT, gameBoard, 3);
        } else {
            crossP = createPlayer(0, P_CROSS, gameBoard, 3);
            noughtP = createPlayer(1, P_NOUGHT, gameBoard, 3);
        }
    } else if (gSetting == SETTING_PVP) {
        crossP = createPlayer(1, P_CROSS, gameBoard, 3);
        noughtP = createPlayer(1, P_NOUGHT, gameBoard, 3);
    } else {
        crossP = createPlayer(0, P_CROSS, gameBoard, 3);
        noughtP = createPlayer(0, P_NOUGHT, gameBoard, 3);
    }
    displayBoard(gameBoard);
    while (!isGameOver(gameBoard)) {
        if (playerTurn) {
            printf("Crosses to move!\n");
            crossP->makeMove(crossP);
            gameBoard[crossP->yMove][crossP->xMove] = P_CROSS;
            displayBoard(gameBoard);
        } else {
            printf("Noughts to move!\n");
            noughtP->makeMove(noughtP);
            gameBoard[noughtP->yMove][noughtP->xMove] = P_NOUGHT;
            displayBoard(gameBoard);
        }
        playerTurn = !playerTurn;
    }
    winningP = isGameWon(gameBoard);
    char *pString;
    switch (winningP) {
        case P_NOUGHT:
            pString = "Noughts has won!\n";
            break;
        case P_CROSS:
            pString = "Crosses has won!\n";
            break;
        default:
            pString = "Draw!\n";
    }
    printf("%s", pString);
    freeBoard(gameBoard);
    free(crossP);
    free(noughtP);
    return 0;
}

int getGameSetting() {
    int gSetting = -1;
    printf("Game Type\n");
    printf("\t(1) Human VS Human\n");
    printf("\t(2) Human VS MCTS_AI\n");
    printf("\t(3) MCTS_AI VS MCTS_AI\n");
    printf("Choose your setting: ");
    gSetting = scanInt();
    while (!(0 < gSetting && gSetting < 4)) {
        gSetting = scanInt();
    }
    return gSetting;
}

int getPlayerSetting() {
    int pSetting = -1;
    printf("Player Side\n");
    printf("\t(1) Noughts\n");
    printf("\t(2) Crosses\n");
    printf("Choose your setting: ");
    pSetting = scanInt();
    while (!(0 < pSetting && pSetting < 3)) {
        pSetting = scanInt();
    }
    if (pSetting == 1) {
        pSetting = P_NOUGHT;
    } else {
        pSetting = P_CROSS;
    }
    return pSetting;
}