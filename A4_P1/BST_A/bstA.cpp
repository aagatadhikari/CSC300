#include "bstA.h"

BST::BST(int size)
{
    capacity = size;
    tree = new int[capacity];
    for(int i = 0; i < size; i++)
        tree[i] = INT_MIN;
}

BST::~BST()
{
    delete[] tree;
}

int BST::leftChild(int index)
{
    return 2 * index + 1;
}

int BST::rightChild(int index)
{
    return 2 * index + 2;
}

int BST::parent(int index)
{
    return (index - 1) / 2;
}

// Iterative insert. A BST stores unique keys, so a duplicate is rejected
// (the original code sent duplicates to the right subtree).
bool BST::insertI(int data)
{
    if(tree[0] == INT_MIN)
    {
        tree[0] = data;
        return true;
    }

    int index = 0;

    while(index < capacity)
    {
        if(data == tree[index])   // duplicate - do not insert
        {
            cout << "Duplicate: " << data << " already in BST, not inserted" << endl;
            return false;
        }
        if(data < tree[index])
        {
            if(leftChild(index) < capacity && tree[leftChild(index)] == INT_MIN)
            {
                tree[leftChild(index)] = data;
                return true;
            }
            index = leftChild(index);
        } else {
            if(rightChild(index) < capacity && tree[rightChild(index)] == INT_MIN)
            {
                tree[rightChild(index)] = data;
                return true;
            }
            index = rightChild(index);
        }
    }

    // walked past the end of the array: the tree is too deep for this capacity
    cout << "No room: " << data << " would go past array capacity" << endl;
    return false;
}

bool BST::insertR(int data)
{
    return insertRhelper(0, data);
}

// Recursive insert with the same duplicate check as insertI
bool BST::insertRhelper(int index, int data)
{
    // Base cases
    if(index >= capacity)
    {
        cout << "No room: " << data << " would go past array capacity" << endl;
        return false;
    }
    if(tree[index] == INT_MIN)
    {
        tree[index] = data;
        return true;
    }
    if(tree[index] == data)   // duplicate - do not insert
    {
        cout << "Duplicate: " << data << " already in BST, not inserted" << endl;
        return false;
    }

    // Recursive case
    if (data < tree[index])
        return insertRhelper(leftChild(index), data);
    else
        return insertRhelper(rightChild(index), data);
}

bool BST::searchI(int data)
{
    int index = 0;

    while(index < capacity)
    {
        if(tree[index] == INT_MIN)
            return false;
        if(tree[index] == data)
            return true;
        if(data < tree[index])
            index = leftChild(index); 
        else
            index = rightChild(index);
    }

    return false;
}

bool BST::searchR(int data)
{
    return searchRhelper(0, data);
}

bool BST::searchRhelper(int index, int data)
{
    // Base case
    if(index >= capacity || tree[index] == INT_MIN)
        return false;
    if(tree[index] == data)
        return true;

    // Recursive case
    if(data < tree[index])
        return searchRhelper(leftChild(index), data);
    else
        return searchRhelper(rightChild(index), data);
}

void BST::preorder(int index) // C-L-R
{
    // base case
    if (index >= capacity || tree[index] == INT_MIN)
        return;

    // recursive case
    cout << tree[index] << " ";
    preorder(leftChild(index));
    preorder(rightChild(index));
}

void BST::inorder(int index) // L-C-R
{
    // base case
    if (index >= capacity || tree[index] == INT_MIN)
        return;

    // recursive case
    inorder(leftChild(index));
    cout << tree[index] << " ";
    inorder(rightChild(index));
}

void BST::postorder(int index) // L-R-C
{
    // base case
    if (index >= capacity || tree[index] == INT_MIN)
        return;

    // recursive case
    postorder(leftChild(index));
    postorder(rightChild(index));
    cout << tree[index] << " ";
}

void BST::printTree(int index, int depth = 0)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;
    
    printTree(rightChild(index), depth + 1);

    for(int i = 0; i < depth; i++)
        cout << "   "; // for indentation
    cout << tree[index] << endl;

    printTree(leftChild(index), depth + 1);
    
}


// ===================================================================
//                Assignment 4 Part 1 - new functions
// ===================================================================

// True when index is outside the array or the slot holds no value
bool BST::isEmptySlot(int index)
{
    return index >= capacity || tree[index] == INT_MIN;
}

// Recursive search that returns WHERE the value lives (-1 if absent)
int BST::findIndex(int index, int data)
{
    if (isEmptySlot(index))
        return -1;
    if (tree[index] == data)
        return index;
    if (data < tree[index])
        return findIndex(leftChild(index), data);
    return findIndex(rightChild(index), data);
}

// Task 1: height of the node at 'index', recomputed recursively every
// call (no stored heights). Height = edges on the longest downward path.
//   empty slot -> -1, leaf -> 0
int BST::height(int index)
{
    // base case: empty subtree
    if (isEmptySlot(index))
        return -1;

    // recursive case: 1 + taller of the two subtrees
    int leftHeight = height(leftChild(index));
    int rightHeight = height(rightChild(index));
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Task 1 (by value): locate the node, then compute its height.
// Returns -2 when the value is not in the tree (-1 already means "empty").
int BST::heightOf(int data)
{
    int index = findIndex(0, data);
    if (index == -1)
        return -2;
    return height(index);
}

// Task 2: count the occupied slots reachable from the root, recursively
int BST::countNodes(int index)
{
    // base case: empty subtree has no nodes
    if (isEmptySlot(index))
        return 0;

    // recursive case: this node + left subtree + right subtree
    return 1 + countNodes(leftChild(index)) + countNodes(rightChild(index));
}

// Task 3: balanced means |height(left) - height(right)| <= 1 at EVERY node.
// Heights are recomputed with height() (no stored values). If an
// imbalance exists, the direction of the highest unbalanced node is
// reported (checked top-down: current node, then left, then right).
string BST::isBalanced(int index)
{
    // base case: empty tree is balanced
    if (isEmptySlot(index))
        return "Yes";

    int diff = height(leftChild(index)) - height(rightChild(index));

    // this node itself is unbalanced
    if (diff > 1)
        return "Left-heavy";
    if (diff < -1)
        return "Right-heavy";

    // this node is fine, so both subtrees must also be balanced
    string leftResult = isBalanced(leftChild(index));
    if (leftResult != "Yes")
        return leftResult;
    return isBalanced(rightChild(index));
}

// Mark every slot in the subtree rooted at index as empty
void BST::clearSubtree(int index)
{
    if (isEmptySlot(index))
        return;
    clearSubtree(leftChild(index));
    clearSubtree(rightChild(index));
    tree[index] = INT_MIN;
}

// Copy the subtree rooted at 'from' in the snapshot 'source' so that it
// is rooted at 'to' in the live array, keeping the same left/right shape.
// Reading from a snapshot means no value is overwritten before it is read.
void BST::copySubtree(int* source, int from, int to)
{
    if (from >= capacity || source[from] == INT_MIN)
        return;
    tree[to] = source[from];
    copySubtree(source, 2 * from + 1, leftChild(to));
    copySubtree(source, 2 * from + 2, rightChild(to));
}

// Remove the value stored at 'index' (the slot is known to be occupied)
void BST::deleteAt(int index)
{
    int left = leftChild(index);
    int right = rightChild(index);
    bool hasLeft = !isEmptySlot(left);
    bool hasRight = !isEmptySlot(right);

    // Case 1: leaf - just empty the slot
    if (!hasLeft && !hasRight)
    {
        tree[index] = INT_MIN;
        return;
    }

    // Case 2: exactly one child - in an array every node's position is
    // fixed by its path from the root, so the child's WHOLE subtree has to
    // move up one level into the deleted node's position.
    if (!hasLeft || !hasRight)
    {
        int child = hasLeft ? left : right;

        // snapshot the array, clear the old area, then rebuild from the snapshot
        int* snapshot = new int[capacity];
        for (int i = 0; i < capacity; i++)
            snapshot[i] = tree[i];

        clearSubtree(index);                    // empties the node and its child subtree
        copySubtree(snapshot, child, index);    // child subtree now starts at index

        delete[] snapshot;
        return;
    }

    // Case 3: two children - copy the inorder successor (smallest value in
    // the right subtree) into this slot, then delete the successor, which
    // has no left child, so it falls into case 1 or 2.
    int successor = right;
    while (!isEmptySlot(leftChild(successor)))
        successor = leftChild(successor);

    tree[index] = tree[successor];
    deleteAt(successor);
}

// Task 4: delete a value from the array BST
bool BST::deleteNode(int data)
{
    int index = findIndex(0, data);
    if (index == -1)
        return false;   // value not in the tree
    deleteAt(index);
    return true;
}

// Task 5: breadth-first (level-order) traversal using the custom Queue.
// The queue holds array indices; each output line is one tree level.
void BST::BFS()
{
    if (isEmptySlot(0))
    {
        cout << "(empty tree)" << endl;
        return;
    }

    Queue<int> q;
    q.enqueue(0);
    int level = 0;

    while (!q.isEmpty())
    {
        // everything currently in the queue belongs to the same level
        int levelSize = q.size();
        cout << "  Level " << level << ": ";

        for (int i = 0; i < levelSize; i++)
        {
            int current = q.dequeue();
            cout << tree[current] << " ";

            // children go to the back of the line for the next level
            if (!isEmptySlot(leftChild(current)))
                q.enqueue(leftChild(current));
            if (!isEmptySlot(rightChild(current)))
                q.enqueue(rightChild(current));
        }
        cout << endl;
        level++;
    }
}
