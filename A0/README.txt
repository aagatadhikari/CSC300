===============================================================
 Assignment 0 - CSC 250 Review
 Fall 2026
===============================================================
 Name:    Aagat Adhikari
 Course:  CSC 250
 Date:    September 5 2026
===============================================================

DESCRIPTION
---------------------------------------------------------------
This assignment starts from the linked list base code covered in
class and completes three tasks:

  Task 1 - Completed the deleteNode() and searchNode() functions
           for the singly linked list.
  Task 2 - Added a reverseList() function that reverses the
           direction of the singly linked list in place.
  Task 3 - Converted the singly linked list into a doubly linked
           list (separate files) with insertNode() and
           deleteNode() implemented.

Both programs are menu driven. The list is printed after every
menu action so the effect of each operation is easy to see.


FILES
---------------------------------------------------------------
Tasks 1 and 2 - singly linked list
  ll.h          Header: node struct and function prototypes
  ll.cpp        Implementation of the singly linked list functions
  main.cpp      Menu driven driver program

Task 3 - doubly linked list
  dll.h         Header: node struct (with prev) and prototypes
  dll.cpp       Implementation of the doubly linked list functions
  main_dll.cpp  Menu driven driver program

Other
  README.txt    This file
  screenshot    Screenshot showing the functions working


HOW TO COMPILE AND RUN
---------------------------------------------------------------
Tasks 1 and 2 (singly linked list):
    g++ main.cpp ll.cpp -o ll
    ./ll

Task 3 (doubly linked list):
    g++ main_dll.cpp dll.cpp -o dll
    ./dll

On Windows the output file is named ll.exe / dll.exe and is run with:  ll.exe  or  dll.exe


Functions in this program 
---------------------------------------------------------------
Singly linked list (ll.h / ll.cpp)

  void insertNode(node *&head, int index, int data)
      Creates a new node holding "data" and links it into the
      list at position "index". Prints a message and does nothing
      if the index is past the end of the list.

  void deleteNode(node *&head, int index)          [Task 1]
      Removes the node at "index" and frees its memory. Handles
      three cases: an empty list, deleting the head (index 0),
      and deleting anywhere else in the list. Prints a message
      if the list is empty or the index does not exist.

  node* searchNode(node *head, int key)            [Task 1]
      Walks the list from the head and returns the address of
      the first node whose data equals "key". Returns nullptr
      and prints a message if the value is not in the list.

  void reverseList(node *&head)                    [Task 2]
      Reverses the list in place using three pointers
      (previous, current, next). No new nodes are created, so
      the function runs in O(n) time using O(1) extra memory.
      The old tail becomes the new head.

  void displayList(node *head)
      Prints every value in the list from head to tail.

Doubly linked list (dll.h / dll.cpp)

  The node struct adds a "prev" pointer so the list can be
  traversed in both directions. Every insert and delete keeps
  both the next and the prev links consistent.

  void insertNode(node *&head, int index, int data) [Task 3]
      Inserts a new node at "index" and repairs the next/prev
      links of the surrounding nodes.

  void deleteNode(node *&head, int index)           [Task 3]
      Removes the node at "index", re-links the neighbours on
      both sides, and frees the memory.

  void displayList(node *head)
      Prints the list forward, following the next pointers.

  void displayListReverse(node *head)
      Prints the list backward, following the prev pointers.
      Included to demonstrate that the prev links are correct.


MENU OPTIONS
---------------------------------------------------------------
Singly linked list (./ll)
  1. Insert a new node
  2. Remove a node
  3. Search for and return a node
  4. Reverse the list
  5. Exit

Doubly linked list (./dll)
  1. Insert a new node
  2. Remove a node
  3. Exit


SAMPLE RUN - singly linked list
---------------------------------------------------------------
  Insert 10 at index 0            -> 10
  Insert 20 at index 1            -> 10 20
  Insert 30 at index 2            -> 10 20 30
  Insert 40 at index 3            -> 10 20 30 40
  Search for 30                   -> 30 was found at memory
                                     address: 0x55bb997d3310
  Search for 99                   -> 99 was not found in the list
  Remove index 1                  -> 10 30 40
  Remove index 0                  -> 30 40
  Remove index 9                  -> Index is too large,
                                     can't delete
  Reverse the list                -> 40 30


SAMPLE RUN - doubly linked list
---------------------------------------------------------------
  Insert 10 at index 0     Forward: 10          Backward: 10
  Insert 20 at index 1     Forward: 10 20       Backward: 20 10
  Insert 30 at index 2     Forward: 10 20 30    Backward: 30 20 10
  Insert 5  at index 0     Forward: 5 10 20 30  Backward: 30 20 10 5
  Remove index 2           Forward: 5 10 30     Backward: 30 10 5
  Remove index 0           Forward: 10 30       Backward: 30 10


NOTES
---------------------------------------------------------------
- Every node created with "new" is released with "delete", both
  when a node is deleted and when the program exits.
- Both programs were compiled and tested with g++ using the
  -Wall flag and produced no warnings.
- Invalid input (empty list, negative index, index past the end
  of the list) is reported to the user instead of crashing.
