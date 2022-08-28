// Author: Rodney Boyce

#ifndef TREE_H
#define TREE_H

#include "list.h"

typedef struct node* Node;
struct node {
    Node parent;
    int player;
    Move nodeMove;
    double winCount;
    double visitCount;
    List validMoves;
    Node nextSibling;
    Node childNode;
};

Node createNode();

void freeTree(Node n);

#endif // TREE_H