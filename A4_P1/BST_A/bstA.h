#ifndef BSTA_H
#define BSTA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <climits>   // INT_MIN marks an empty slot
#include "queue.h"   // custom queue used by BFS()

using namespace std;

class BST
{
    private:
        int* tree;
        int capacity;

        int leftChild(int index);
        int rightChild(int index);
        int parent(int index);

        // helpers for the new functions
        bool isEmptySlot(int index);                      // out of range or INT_MIN
        int findIndex(int index, int data);               // recursive search that returns the index (-1 if absent)
        void deleteAt(int index);                         // removes the value stored at index
        void clearSubtree(int index);                     // marks a whole subtree as empty
        void copySubtree(int* source, int from, int to);  // copies a subtree from a snapshot to a new position

    public:
        BST(int size);
        ~BST();

        // Return true if inserted, false for a duplicate or no room in the array
        bool insertI(int data);
        bool insertR(int data);
        bool insertRhelper(int index, int data);

        bool searchI(int data);
        bool searchR(int data);
        bool searchRhelper(int index, int data);

        void preorder(int index = 0);
        void inorder(int index = 0);
        void postorder(int index = 0);

        void printTree(int index, int depth);

        // ---------------- Assignment 4 Part 1 additions ----------------
        int height(int index = 0);          // Task 1: height of node at index (edges); empty = -1, leaf = 0
        int heightOf(int data);             // Task 1: height of the node holding 'data' (-2 if not found)
        int countNodes(int index = 0);      // Task 2: total number of nodes
        string isBalanced(int index = 0);   // Task 3: "Yes", "Left-heavy" or "Right-heavy"
        bool deleteNode(int data);          // Task 4: delete a value, false if not found
        void BFS();                         // Task 5: level-order traversal using the custom queue
};

#endif
