#include "bstP.h"

node::node(int value)
{
    data = value;
    leftChild = nullptr;
    rightChild = nullptr;
}

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(node* node)
{
    if(node == nullptr)
        return;
    
    clearTree(node->leftChild);
    clearTree(node->rightChild);
    delete node;
}

// Insert a value while keeping the BST property.
// A BST holds unique keys, so a duplicate value is rejected (returns false)
// instead of being placed in the right subtree as the original code did.
bool BST::insertNode(node*& root, int data)
{
    if(root == nullptr)
    {
        root = new node(data);
        return true;
    }

    if(data == root->data)          // duplicate found - do not insert
        return false;
    if(data < root->data)
        return insertNode(root->leftChild, data);
    else
        return insertNode(root->rightChild, data);
}

node* BST::searchNode(node*& root, int data)
{
    if (root == nullptr || root->data == data)
        return root;
    if (data < root->data)
        return searchNode(root->leftChild, data);
    return searchNode(root->rightChild, data);
}

void BST::deleteNode(node*& root, int data)
{
    if (root == nullptr)
        return;

    if (data < root->data)
        deleteNode(root->leftChild, data);
    else if (data > root->data)
        deleteNode(root->rightChild, data);
    else {
        if (root->leftChild == nullptr) {
            node* temp = root->rightChild;
            delete root;
            root = temp;
        }
        else if (root->rightChild == nullptr) {
            node* temp = root->leftChild;
            delete root;
            root = temp;
        }
        else {
            node* temp = root->rightChild;
            while (temp->leftChild != nullptr)
                temp = temp->leftChild;
            root->data = temp->data;
            deleteNode(root->rightChild, temp->data);
        }
    }
}

void BST::preorder(node* root)
{
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorder(root->leftChild);
    preorder(root->rightChild);
}

void BST::inorder(node* root)
{
    if (root == nullptr)
        return;
    inorder(root->leftChild);
    cout << root->data << " ";
    inorder(root->rightChild);
}

void BST::postorder(node* root)
{
    if (root == nullptr)
        return;
    postorder(root->leftChild);
    postorder(root->rightChild);
    cout << root->data << " ";
}


void BST::printTree(node* root, int space)
{
    const int COUNT = 10;
    if (root == nullptr)
        return;
    space += COUNT;
    printTree(root->rightChild, space);
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->data << endl;
    printTree(root->leftChild, space);
}


// ===================================================================
//                Assignment 4 Part 1 - new functions
// ===================================================================

// Task 1: height of the given node, computed recursively every call
// (nothing is stored in the nodes). Height = number of edges on the
// longest path from this node down to a leaf.
//   empty subtree -> -1, leaf -> 0
int BST::height(node* root)
{
    // base case: empty subtree
    if (root == nullptr)
        return -1;

    // recursive case: 1 + taller of the two subtrees
    int leftHeight = height(root->leftChild);
    int rightHeight = height(root->rightChild);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Task 2: count every node recursively (no stored counter).
int BST::countNodes(node* root)
{
    // base case: empty subtree has no nodes
    if (root == nullptr)
        return 0;

    // recursive case: this node + nodes on the left + nodes on the right
    return 1 + countNodes(root->leftChild) + countNodes(root->rightChild);
}

// Task 3: a tree is balanced when, at EVERY node, the heights of the
// left and right subtrees differ by at most 1. Heights are recomputed
// with height() each time (no stored values).
// If an imbalance is found, the direction is reported for the highest
// unbalanced node (checked top-down: current node, then left, then right):
//   left subtree taller  -> "Left-heavy"
//   right subtree taller -> "Right-heavy"
string BST::isBalanced(node* root)
{
    // base case: an empty tree is balanced
    if (root == nullptr)
        return "Yes";

    int diff = height(root->leftChild) - height(root->rightChild);

    // this node itself is unbalanced
    if (diff > 1)
        return "Left-heavy";
    if (diff < -1)
        return "Right-heavy";

    // this node is fine, so both subtrees must also be balanced
    string leftResult = isBalanced(root->leftChild);
    if (leftResult != "Yes")
        return leftResult;
    return isBalanced(root->rightChild);
}

// Task 5: breadth-first (level-order) traversal using the custom Queue.
// Each line of output is one level of the tree.
void BST::BFS(node* root)
{
    if (root == nullptr)
    {
        cout << "(empty tree)" << endl;
        return;
    }

    Queue<node*> q;
    q.enqueue(root);
    int level = 0;

    while (!q.isEmpty())
    {
        // everything currently in the queue belongs to the same level
        int levelSize = q.size();
        cout << "  Level " << level << ": ";

        for (int i = 0; i < levelSize; i++)
        {
            node* current = q.dequeue();
            cout << current->data << " ";

            // children go to the back of the line for the next level
            if (current->leftChild != nullptr)
                q.enqueue(current->leftChild);
            if (current->rightChild != nullptr)
                q.enqueue(current->rightChild);
        }
        cout << endl;
        level++;
    }
}
