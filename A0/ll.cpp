/*
 Singly linked list implementation     
 Task 1 - deleteNode() and searchNode() completed below
 Task 2 - reverseList() added below

 */

#include "ll.h"

// insertNode Creates a new node and links it into the list at the given index.
void insertNode(node *&head, int index, int data)
{
    node* newNode = new node;
    newNode->data = data;
    newNode->next = nullptr;

    if(index == 0)
    {
        // Inserting at the front: the new node points at the old head
        // and then becomes the head itself.
        newNode->next = head;
        head = newNode;
    }
    else
    {
        // Walk to the node that sits just before  the target index.
        node* walker = head;
        int wIndex = 0;
        while(walker != NULL && wIndex < index-1)
        {
            walker = walker->next;
            wIndex++;
        }
        if(walker == nullptr)
        {
            cout << "Index is too large, can't insert" << endl;
            return;
        }
        else
        {
            newNode->next = walker->next;
            walker->next = newNode;
        }
    }
}

/*
deleteNode , Removes the node found at "index" from the list and releases its memory.
Nothing happens  if the list is empty or the index is past the end of the list.
 */
void deleteNode(node *&head, int index)
{
    // Check if the list is empty 
    if(head == nullptr)
    {
        cout << "List is empty, nothing to delete" << endl;
        return;
    }

    // A negative index is not a valid position in the list
    if(index < 0)
    {
        cout << "Invalid index, can't delete" << endl;
        return;
    }

    // Check if we are deleting at index 0 and handle accordingly
    if(index == 0)
    {
        // Remember the current head, move head forward, then free the old head.
        node* temp = head;
        head = head->next;
        delete temp;
    }
    // Handle other index deletions
    else
    {
        // Walk to the node just before the one we want to remove.
        node* walker = head;
        int wIndex = 0;
        while(walker != nullptr && wIndex < index-1)
        {
            walker = walker->next;
            wIndex++;
        }

        // walker is null  -> we ran off the end of the list
        // walker->next is null -> there is no node at index
        if(walker == nullptr || walker->next == nullptr)
        {
            cout << "Index is too large, can't delete" << endl;
            return;
        }

        // Unlink the target node and free it.
        node* target = walker->next;
        walker->next = target->next;
        delete target;
    }
}

//displayList Prints each value in the list separated by spaces.
 
void displayList(node *head)
{
    node* walker = head;

    while(walker != nullptr)
    {
        cout << walker->data<<" ";
        walker = walker->next;
    }
    cout<<endl;
}

/*
 searchNode (Task 1)
 Traverses the list from the head looking for "key".
Returns the address of the first matching node, or nullptr if the value never appears in the list.
 */
node* searchNode(node *head, int key)
{
    node* walker = head;

    while(walker != nullptr)
    {
        if(walker->data == key)
        {
            return walker;      // found it , hand back the node's address
        }
        walker = walker->next;
    }

    // Fell off the end of the list without a match.
    cout << key << " was not found in the list" << endl;
    return nullptr;
}

/*
 reverseList  (Task 2)  Reverses the list in place using three pointers:
 previous - the node already reversed (what current should point to)
 current  - the node being re-pointed right now
 nextNode - saves the rest of the list before we overwrite the link
Runs in O(n) time and uses O(1) extra memory - no new nodes are created.
 */
void reverseList(node *&head)
{
    node* previous = nullptr;
    node* current  = head;
    node* nextNode = nullptr;

    while(current != nullptr)
    {
        nextNode = current->next;   // save the remainder of the list
        current->next = previous;   // flip this node's link backwards
        previous = current;         // slide both pointers forward
        current = nextNode;
    }

    // previous is sitting on the old tail, which is now the new head.
    head = previous;
}
