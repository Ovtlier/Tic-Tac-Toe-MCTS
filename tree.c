// Author: Rodney Boyce

#include "tree.h"

#include <stdlib.h>

void freeTree(Node n) {
    if (n == NULL) {
        return;
    }
    freeTree(n->childNode);
    freeTree(n->nextSibling);
    
    freeList(n->validMoves);
    free(n);
}

Node createNode() {
    Node newN = malloc(sizeof(*newN));
    newN->parent = NULL;
    newN->player = -1;
    newN->nodeMove = -1;
    newN->winCount = 0;
    newN->visitCount = 0;
    newN->validMoves = NULL;
    newN->nextSibling = NULL;
    newN->childNode = NULL;
    return newN;
}

