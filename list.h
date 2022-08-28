// Author: Rodney Boyce

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef int Move;

typedef struct list* List;

//  Creates and returns a new empty memory allocated list
//      Params: None
//
//      Return: struct list *   (typedef'd as List)
List createList();

//  Adds an item to the back of the list.
//      Params: struct list *   (typedef'd as List)
//              int             (typedef's as Move)
//
//      Return: void
void addItemToList(List l, Move m);

//  Removes a random node in the list, returns the item of that node (int).
//      Params: struct list *   (typedef'd as List)
//
//      Return: int             (typedef'd as Move)
Move popListRand(List l);

//  Removes the front node in the list, returns the item of that node (int).
//  Used in queues (FIFO).
//      Params: struct list *   (typedef'd as List)
//      
//      Return: int             (typedef'd as Move)
Move popListFront(List l);

//  Removes the back node in the list, returns the item of that node (int).
//  Used in stacks (FILO).
//      Params: struct list *   (typedef'd as List)
//
//      Return: int             (typedef's as Move)
Move popListBack(List l);

//  Frees the given list
//      Params: struct list *   (typedef'd as List)
//
//      Return: void
void freeList(List l);

bool isListEmpty(List l);

#endif // LIST_H