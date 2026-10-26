Assignment 4 Part 2 - Augmented BST (Single Runway Landing Reservation)

Aagat Adhikari
Course: CSC 300, Fall 2026

FILES
  reserve.h        - BST node struct and BST class declarations
  reserve.cpp      - Implementation of checkConflict(), insert(), countPlanes()
  mainR.cpp        - Main program (reads landing times, prints results)
  screenshot.png   - Output showing the functions working

HOW TO COMPILE
  g++ -std=c++11 -Wall -Wextra -o runway.exe reserve.cpp mainR.cpp

HOW TO RUN
  runway.exe

  Enter landing times in minutes past midnight, one per line.
  Enter -1 to stop adding times.
  Enter a time to count how many planes land at or before that time.

EXAMPLE INPUT
  600
  602
  603
  610
  605
  700
  -1
  650

EXPECTED OUTPUT
  600 reserved, 602 conflict, 603 reserved, 610 reserved,
  605 conflict, 700 reserved
  In-order: 600 603 610 700
  Planes at or before 650: 3

DESIGN NOTES
  - checkConflict() (Task 1) is recursive. It goes left or right at each node,
    since only one side can hold a conflict. Time is O(height) of the tree.
  - insert() (Task 2) is recursive. It places the time, skips duplicates, and
    recalculates subtreeSize on the way back up.
  - countPlanes() (Task 3) is recursive. If a node's time is at or before t,
    the node, its whole left subtree, and the matching part of the right
    subtree are counted. Subtree sizes make this O(height).

ASSUMPTIONS
  - Two landings conflict when they are less than 3 minutes apart.
    Times exactly 3 minutes apart are allowed.
  - Duplicate times are ignored by insert().

CHANGES TO THE BASE CODE
  - clearTree() checked root instead of node, which crashed on recursion.
    It now checks node.
  - main() called insert() after reserve(), but reserve() already inserts.
    The extra call was removed so times are not inserted twice.