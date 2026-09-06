/*
  main_dll.cpp
   Driver / menu for the DOUBLY linked list (Task 3).
 
  Build:  g++ main_dll.cpp dll.cpp -o dll
  Run:    ./dll
 
 */

#include "dll.h"

int main()
{
    node *head = nullptr;       // the list starts out empty

    int choice, data, index;

    do {
        cout << endl;
        cout << "1. Insert a new node" << endl;
        cout << "2. Remove a node" << endl;
        cout << "3. Exit" << endl << endl;

        cin >> choice;

        switch(choice)
        {
            case 1:
                cout << "What value do you want to insert:  ";
                cin >> data;
                cout << "Which index do want to insert at:  ";
                cin >> index;
                insertNode(head, index, data);
                break;
            case 2:
                cout << "Which index do you want to remove:  ";
                cin >> index;
                deleteNode(head, index);
                break;
            case 3:
                cout << "See you" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }

        // Printing both directions shows the prev links are correct.
        cout << "Forward:   ";
        displayList(head);
        cout << "Backward:  ";
        displayListReverse(head);

    } while (choice != 3);

    // Clean up any nodes still in the list.
    while(head != nullptr)
    {
        deleteNode(head, 0);
    }

    return 0;
}
