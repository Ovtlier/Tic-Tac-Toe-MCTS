// Author: Rodney Boyce

#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node* Node;

struct node {
    Move move;
    Node next;
    Node prev;
};

struct list {
    Node head;
    Node tail;
    int listSize;
};

//  Creates a new node that holds the value of the given param
//      Params: int             (typedef'd as Move)
//
//      Return: struct node *   (typedef'd as Node)
static Node createNode(Move m);

List createList() {
    List newList = malloc(sizeof(*newList));
    if (newList == NULL) {
        fprintf(stderr, "Failed to allocate memory for a new list.\n");
        exit(EXIT_FAILURE);
    }
    newList->head = NULL;
    newList->tail = NULL;
    newList->listSize = 0;
    return newList;
}

void addItemToList(List l, Move m) {
    assert(l != NULL);
    Node newNode = createNode(m);
    if (l->listSize == 0) {
        l->head = l->tail = newNode;
    } else {
        newNode->prev = l->tail;
        l->tail->next = newNode;
        l->tail = newNode;
    }
    l->listSize++;
}

Move popListRand(List l) {
    int randNum = rand() % l->listSize;
    Node curr = l->head;
    for (int i = 0; i < randNum; i++) {
        curr = curr->next;
    }
    Move tempMove = curr->move;
    if (l->listSize == 1) {
        l->head = NULL;
        l->tail = NULL;
    } else if (curr->prev == NULL) {
        curr->next->prev = NULL;
        l->head = curr->next;
    } else if (curr->next == NULL) {
        curr->prev->next = NULL;
        l->tail = curr->prev;
    } else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
    free(curr);
    l->listSize--;
    return tempMove;
}

Move popListFront(List l) {
    assert(l != NULL);
    assert(l->listSize > 0);

    Move poppedMove = l->head->move;
    Node newHead = l->head->next;
    free(l->head);
    l->head = newHead;
    if (newHead == NULL) {
        l->tail = NULL;
    } else {
        l->head->prev = NULL;
    }
    l->listSize--;
    return poppedMove;
}

Move popListBack(List l) {
    assert(l != NULL);
    assert(l->listSize > 0);

    Move poppedMove = l->tail->move;
    Node newTail = l->tail->prev;
    free(l->tail);
    l->tail = newTail;
    if (newTail == NULL) {
        l->head = NULL;
    } else {
        l->tail->next = NULL;
    }
    l->listSize--;
    return poppedMove;
}

void freeList(List l) {
    Node curr = l->head;
    while (curr != NULL) {
        Node nodeToDel = curr;
        curr = curr->next;
        free(nodeToDel);
    }
    free(l);
}

static Node createNode(Move m) {
    Node newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate memory for a new node.\n");
        exit(EXIT_FAILURE);
    }
    newNode->move = m;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

bool isListEmpty(List l) {
    return (l->listSize == 0);
}