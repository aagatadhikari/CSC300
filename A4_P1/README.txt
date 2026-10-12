Assignment 4 Part 1 - BST with arrays and pointers
===================================================
Author: Aagat Adhikari
Course term: Fall 2026

Folder contents
---------------
A4_P1/
  README.txt              this file
  screenshot_BST_A.png    output of the array version running inst.txt
  screenshot_BST_P.png    output of the pointer version running inst.txt
  BST_A/                  array-based BST
      bstA.h, bstA.cpp, mainA.cpp, queue.h, inst.txt
  BST_P/                  pointer (linked) BST
      bstP.h, bstP.cpp, mainP.cpp, queue.h, inst.txt

How to compile and run
----------------------
  cd BST_A
  g++ -std=c++17 -Wall -o bstA mainA.cpp bstA.cpp
  ./bstA inst.txt

  cd BST_P
  g++ -std=c++17 -Wall -o bstP mainP.cpp bstP.cpp
  ./bstP inst.txt

(queue.h is header-only, so it does not need to be listed on the g++ line.)

Input commands
--------------
BST_A (array)                         BST_P (pointers)
  0      exit                           0      exit
  1 x    insert x (iterative)           1 x    insert x
  2 x    insert x (recursive)           2 x    search x
  3 x    search x (iterative)           3 x    delete x
  4 x    search x (recursive)           4      inorder
  5      preorder                       5      preorder
  6      inorder                        6      postorder
  7      postorder                      7      print tree
  8      print tree                     8 [x]  height of node x (tree height if no x)
  9 [x]  height of node x               9      count nodes
         (tree height if no x)          10     is balanced?
  10     count nodes                    11     BFS traversal
  11     is balanced?
  12 x   delete x
  13     BFS traversal

The original commands from the base code keep their numbers; the new
ones are added after them.

What was implemented
--------------------
Task 1 - height()
  Recursive in both versions. Height is measured in edges:
  an empty subtree is -1, a leaf is 0, and a node's height is
  1 + max(height(left), height(right)). Nothing is stored in the nodes;
  the height is recomputed on every call. "height of a given node" is
  done by finding the node (searchNode for BST_P, findIndex for BST_A)
  and calling height() on it.

Task 2 - countNodes()
  Recursive: 0 for an empty subtree, otherwise
  1 + countNodes(left) + countNodes(right). No stored counter.

Task 3 - isBalanced()
  A tree is balanced when, at every node, the left and right subtree
  heights differ by at most 1. The function checks the current node
  using height(), then recurses into the left and right subtrees.
  It returns "Yes" if every node passes. If a node fails, it returns
  "Left-heavy" when that node's left subtree is taller or
  "Right-heavy" when its right subtree is taller. The direction reported
  is that of the highest unbalanced node (checked top-down: current node,
  then left subtree, then right subtree).

Duplicate insertions
  A BST stores unique keys, so insertNode (BST_P) and insertI / insertR
  (BST_A) now return false and do not insert when the value already
  exists. Previously, duplicates were sent to the right subtree.
  main prints "Duplicate: x already in BST, not inserted".

  The array insert functions also now report "No room" when a value
  would land beyond the end of the array. The base code dropped these
  silently. With the default capacity of 50, levels 0-4 fit fully
  (indices 0-30) but level 5 only partly (indices 31-49). In the
  original test input, 19 and 14 would need indices 58 and 57, so they
  are reported this way.

Task 4 - deleteNode() for BST_A
  In an array BST a node's position is fixed by its path from the root,
  so deleting is more than clearing a slot. Three cases:
    1. Leaf: set the slot back to INT_MIN.
    2. One child: the child's ENTIRE subtree moves up one level into the
       deleted node's position. The array is copied to a snapshot first,
       then the old area is cleared and the subtree is rebuilt from the
       snapshot (copySubtree). This avoids overwriting a value before it
       has been read.
    3. Two children: copy the inorder successor (smallest value in the
       right subtree) into the slot, then delete the successor (which has
       no left child, so it is case 1 or 2).
  deleteNode returns false (and main prints "not found") if the value is
  not in the tree.

Task 5 - BFS()
  Level-order traversal using the custom linked-list Queue in queue.h
  (templated so it holds node* for BST_P and array indices for BST_A).
  No STL queue is used. The root goes in the queue; each step dequeues a
  node, prints it and enqueues its children. The output is printed one
  level per line.

Test input (inst.txt)
---------------------
Both inst.txt files start with the original base-code inserts and then
test every new feature: duplicates, height of the tree / of specific
nodes / of a missing value, node count, BFS, and all three isBalanced
results (Right-heavy, Left-heavy and Yes). For BST_A, inst.txt also
deletes a leaf (40), a node with one child (0), nodes with two children
(20, the root 7), a node with one child that carries a deep subtree (9),
and a missing value (100).

Both versions were also checked with a randomized test of thousands of
insert/delete sequences against std::set, built with AddressSanitizer:
no wrong results and no memory errors.
