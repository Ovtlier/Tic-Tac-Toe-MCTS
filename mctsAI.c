// Author: Rodney Boyce

#include "mctsAI.h"

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>

#define MCTS_ITERATIONS 400000

static double calcUCT(Node n);
static Node mctsSelection(Node root, int **b);
static Node mctsExpansion(Node n, int **b);
static int mctsSimulation(int **b, int p);
static void mctsBackpropogate(Node n, int mctsPlayer, int playerWhoWon);
static List getValidMoves(int **b);
static void addMoveToBoard(int **b, Move m, int p);
static Node getBestNode(Node n);

Move doMCTS(int **b, int p) {
    int **simBoard = createBoard();

    Node rootN = createNode();
    rootN->player = !p;
    rootN->validMoves = getValidMoves(b);

    for (int i = 0; i < MCTS_ITERATIONS; i++) {
        //printf("New Simulation.\n");
        copyBoard(simBoard, b);
        //printf("Selection:\n");
        Node selectedChild = mctsSelection(rootN, simBoard);
        //printf("Expansion:\n");
        selectedChild = mctsExpansion(selectedChild, simBoard);
        //printf("Simulation:\n");
        int playerWhoWon = mctsSimulation(simBoard, !selectedChild->player);
        mctsBackpropogate(selectedChild, p, playerWhoWon);
    }
    Node bestNode = getBestNode(rootN->childNode);
    Move bestMove = bestNode->nodeMove;
    printf("Parent: %f / %f\n", rootN->winCount, rootN->visitCount);
    printf("Best Node: %f / %f\n", bestNode->winCount, bestNode->visitCount);
    printf("Best Move: %d, %d\n", (bestMove % 3) + 1, (bestMove / 3) + 1);
    freeTree(rootN);
    //printf("Free'd tree\n");
    freeBoard(simBoard);
    //printf("Free'd board\n");

    return bestMove;
}

static double calcUCT(Node n) {
    double fPart = n->winCount / n->visitCount;
    double sPart = sqrt(2.0 * (log(n->parent->visitCount) / n->visitCount));
    return fPart + sPart;
}

static Node mctsSelection(Node root, int **b) {
    Node selectedNode = root;
    while (isListEmpty(selectedNode->validMoves) && selectedNode->childNode != NULL) {
        Node curr = selectedNode->childNode;
        double maxUCT = -DBL_MAX;
        while (curr != NULL) {
            double tempUCT = calcUCT(curr);
            if (tempUCT > maxUCT) {
                maxUCT = tempUCT;
                selectedNode = curr;
            }
            curr = curr->nextSibling;
        }
        addMoveToBoard(b, selectedNode->nodeMove, selectedNode->player);
        //displayBoard(b);
    }
    return selectedNode;
}

static Node mctsExpansion(Node n, int **b) {
    if (!isGameOver(b)) {
        Move tempMove = popListRand(n->validMoves);

        Node newNode = createNode();
        newNode->parent = n;
        newNode->player = !n->player;
        newNode->nodeMove = tempMove;
        addMoveToBoard(b, tempMove, newNode->player);
        //displayBoard(b);
        newNode->validMoves = getValidMoves(b);

        if (n->childNode == NULL) {
            n->childNode = newNode;
        } else {
            Node curr = n->childNode;
            while (curr->nextSibling != NULL) {
                curr = curr->nextSibling;
            }
            curr->nextSibling = newNode;
        }

        return newNode;
    }
    return n;
}

static int mctsSimulation(int **b, int p) {
    List l = getValidMoves(b);
    int playerTurn = p;
    while (!isGameOver(b)) {
        Move moveToSim = popListRand(l);
        addMoveToBoard(b, moveToSim, playerTurn);
        //displayBoard(b);
        playerTurn = !playerTurn;
    }
    freeList(l);
    return isGameWon(b);
}

static void mctsBackpropogate(Node n, int mctsPlayer, int playerWhoWon) {
    Node curr = n;
    if (playerWhoWon == mctsPlayer) {
        while (curr != NULL) {
            if (curr->player == mctsPlayer) {
                curr->winCount += 1.0;
            }
            curr->visitCount += 1.0;
            curr = curr->parent;
        }
    } else if (playerWhoWon == !mctsPlayer) {
        while (curr != NULL) {
            if (curr->player != mctsPlayer) {
                curr->winCount += 1.0;
            }
            curr->visitCount += 1.0;
            curr = curr->parent;
        }
    } else {
        while (curr != NULL) {
            curr->winCount += 0.5;
            curr->visitCount += 1.0;
            curr = curr->parent;
        }
    }
}

static List getValidMoves(int **b) {
    List l = createList();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == EMPTY_CELL) {
                int tempMove = (i * 3) + j;
                addItemToList(l, tempMove);
            }
        }
    }
    return l;
}

static void addMoveToBoard(int **b, Move m, int p) {
    int yMove = m / 3;
    int xMove = m % 3;
    b[yMove][xMove] = p;
}

static Node getBestNode(Node n) {
    assert(n != NULL);
    Node bestNode;
    Node curr = n;
    double bestScore = 0.0;
    while (curr != NULL) {
        double currScore = curr->winCount / curr->visitCount;
        if (currScore > bestScore) {
            bestScore = currScore;
            bestNode = curr;
        }
        curr = curr->nextSibling;
    }
    return bestNode;
}