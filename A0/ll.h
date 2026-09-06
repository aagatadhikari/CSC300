//  Header file for the S linked list implementation. task 1 and 2 

#ifndef LL_H
#define LL_H

#include <iostream>
using namespace std;

/*
 A single element (node) of the linked list.
  data - the integer value stored in this node
   next - pointer to the following node, nullptr if this is the last node
 */
struct node
{
    int data;
    struct node *next;
};

/*
 insertNode Inserts a new node holding "data" at position "index" of the list.
  head is passed by reference because inserting at index 0 changes it.
 */
void insertNode(node *&head, int index, int data);

/*
  deleteNode  (Task 1)
  Removes the node at position "index" and frees its memory.
  head is passed by reference because deleting index 0 changes it.
 */
void deleteNode(node *&head, int index);

/*
  displayList
  Prints every value in the list from head to tail.
 */
void displayList(node *head);

/*
  searchNode  (Task 1)
  Walks the list looking for the first node whose data equals "key".
  Returns a pointer to that node, or nullptr if the key is not found.
 */
node* searchNode(node *head, int key);

/*
  reverseList  (Task 2)
  Reverses the direction of the list in place, so the old tail becomes
  the new head. head is passed by reference because it is updated.
 */
void reverseList(node *&head);

#endif
