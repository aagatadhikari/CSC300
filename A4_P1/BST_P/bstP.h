#ifndef BSTP_H
#define BSTP_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "queue.h"   // custom queue used by BFS()

using namespace std;

struct node
{
    int data;
    node* leftChild;
    node* rightChild;

    node(int value);
};

class BST
{
    public:
        node* root;

        BST();
        ~BST();
        void clearTree(node* node);

        // Returns true if inserted, false if the value is a duplicate
        bool insertNode(node*& root, int data);
        node* searchNode(node*& root, int data);
        void deleteNode(node*& root, int data);

        void preorder(node* root);
        void inorder(node* root);
        void postorder(node* root);

        void printTree(node* root, int space);

        // ---------------- Assignment 4 Part 1 additions ----------------
        int height(node* root);          // Task 1: height of a node (edges); empty = -1, leaf = 0
        int countNodes(node* root);      // Task 2: total number of nodes
        string isBalanced(node* root);   // Task 3: "Yes", "Left-heavy" or "Right-heavy"
        void BFS(node* root);            // Task 5: level-order traversal using the custom queue
};

#endif
