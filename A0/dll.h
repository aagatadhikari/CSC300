/*
 dll.h
Header file for doubly linked lists task3 
 */

#ifndef DLL_H
#define DLL_H

#include <iostream>
using namespace std;

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

/*
 insertNode  Inserts a new node holding data at position index
 Both the next and prev links of the surrounding nodes are repaired.
 */
void insertNode(node *&head, int index, int data);

/*
deleteNode  
  Removes the node at position index and frees its memory,
  re-linking the neighbours on both sides.
 */
void deleteNode(node *&head, int index);


//  displayList prints the list from head to tail (follows the next pointers).
 
void displayList(node *head);

/*
  displayListReverse prints the list from tail to head (follows the prev pointers).
 This exists to prove the backward links are maintained correctly.
 */
void displayListReverse(node *head);

#endif
