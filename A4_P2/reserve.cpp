#include "reserve.h"

// Returns the subtree size of a node (0 for an empty subtree).
static int sizeOf(reservation* node)
{
    return (node == nullptr) ? 0 : node->subtreeSize;
}

reservation::reservation(int t) {
    time = t;
    left = nullptr;
    right = nullptr;
    subtreeSize = 1; // a new node is a subtree of size 1 by itself
}


BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

// Frees every node in the subtree rooted at node (post-order)
void BST::clearTree(reservation* node)
{
    if (node == nullptr)   // was "root == nullptr", which crashes on the recursive calls
        return;

    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// reserve new landing time
bool BST::reserve(int time)
{
    if (checkConflict(root, time)) {
        return false; // conflict - reservation fails
    }

    insert(root, time);
    return true; // no conflict - reservation successful
}

// Task 1: returns true if 'time' is within 3 minutes of any scheduled time.
// Recursive BST search: at each node, only one side can contain a conflict,
// so we go left or right instead of visiting both (O(height) time).
bool BST::checkConflict(reservation* node, int time)
{
    if (node == nullptr)
        return false;

    if (abs(node->time - time) < 3)   // closer than 3 minutes -> conflict
        return true;

    if (time < node->time)
        return checkConflict(node->left, time);
    else
        return checkConflict(node->right, time);
}

// Task 2: insert a time (assumed conflict-free) and update subtree sizes.
// Duplicate times are ignored.
void BST::insert(reservation*& node, int time)
{
    if (node == nullptr) {
        node = new reservation(time);   // subtreeSize = 1 from the constructor
        return;
    }

    if (time == node->time)             // avoid inserting duplicates
        return;

    if (time < node->time)
        insert(node->left, time);
    else
        insert(node->right, time);

    // Subtree size of this node = itself + sizes of both children
    node->subtreeSize = 1 + sizeOf(node->left) + sizeOf(node->right);
}

// Task 3: count nodes with times <= t (recursive).
// If node->time <= t, the node itself, its entire left subtree, and the
// matching part of the right subtree all qualify.
int BST::countPlanes(reservation* node, int t)
{
    if (node == nullptr)
        return 0;

    if (node->time <= t)
        return 1 + sizeOf(node->left) + countPlanes(node->right, t);
    else
        return countPlanes(node->left, t);
}

void BST::inorder(reservation* root)
{
    if (root == nullptr)
        return;

    inorder(root->left);
    cout << root->time << " ";
    inorder(root->right);
}