
//Double linked list - Task 3 
 

#include "dll.h"
/*
 insertNode  (Task 3)
 Creates a new node and splices it into the list in index 
 setting both the next and the prev pointers on every node are involved
 */
void insertNode(node *&head, int index, int data)
{
    node* newNode = new node;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if(index < 0)
    {
        cout << "Invalid index, can't insert" << endl;
        delete newNode;
        return;
    }

    if(index == 0)
    {
        // Inserting at the front of the list.
        newNode->next = head;

        // If list was not empty,  old head now points back at us.
        if(head != nullptr)
        {
            head->prev = newNode;
        }

        head = newNode;         // new node becomes the head and its prev stays null
    }
    else
    {
        // Walk to the node that sits just BEFORE the target index.
        node* walker = head;
        int wIndex = 0;
        while(walker != nullptr && wIndex < index-1)
        {
            walker = walker->next;
            wIndex++;
        }

        if(walker == nullptr)
        {
            cout << "Index is too large, can't insert" << endl;
            delete newNode;
            return;
        }

        // Link new node in between walker and walker->next.
        newNode->next = walker->next;
        newNode->prev = walker;

        // If we are not inserting at the very end, the node after us has to point back at the new node.
    
        if(walker->next != nullptr)
        {
            walker->next->prev = newNode;
        }

        walker->next = newNode;
    }
}


 // deleteNode , Removes the node at index and frees it. 
void deleteNode(node *&head, int index)
{
    // Check if the list is empty 
    if(head == nullptr)
    {
        cout << "List is empty, nothing to delete" << endl;
        return;
    }

    if(index < 0)
    {
        cout << "Invalid index, can't delete" << endl;
        return;
    }

    // Walk to the node we actually want to remove.
    node* target = head;
    int wIndex = 0;
    while(target != nullptr && wIndex < index)
    {
        target = target->next;
        wIndex++;
    }

    if(target == nullptr)
    {
        cout << "Index is too large, can't delete" << endl;
        return;
    }

    // Repair the link coming from the left side.
    if(target->prev != nullptr)
    {
        target->prev->next = target->next;
    }
    else
    {
        // No previous node means we removed the head.
        head = target->next;
    }

    // Repair the link coming from the right side.
    if(target->next != nullptr)
    {
        target->next->prev = target->prev;
    }

    delete target;
}

// displayList , Prints the list head -> tail by following the next pointers.
 
void displayList(node *head)
{
    node* walker = head;

    while(walker != nullptr)
    {
        cout << walker->data << " ";
        walker = walker->next;
    }
    cout << endl;
}

/*
 displayListReverse
  Walks to the tail with the next pointers, then prints the list 
  tail -> head using only the prev pointers.
 */
void displayListReverse(node *head)
{
    if(head == nullptr)
    {
        cout << endl;
        return;
    }

    node* walker = head;
    while(walker->next != nullptr)      // find the tail
    {
        walker = walker->next;
    }

    while(walker != nullptr)            // now walk backwards
    {
        cout << walker->data << " ";
        walker = walker->prev;
    }
    cout << endl;
}
