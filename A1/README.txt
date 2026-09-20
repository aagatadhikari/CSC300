===============================================================
 Assignment 1 - Stacks and Queues
 Fall 2026
===============================================================
 Name:    Aagat Adhikari
 Course:  CSC 300
 Date:    September 2026
===============================================================

DESCRIPTION
---------------------------------------------------------------
This assignment starts from the linked list stack and queue base
code from class and finishes four tasks:

  Task 1 - push() and pop() for the Stack
  Task 2 - enqueue() and dequeue() for the Queue
  Task 3 - Dijkstra's two stack algorithm to evaluate a fully
           parenthesized expression, with + - * / and ^
  Task 4 - Josephus problem with N soldiers, solved with a queue

The program is menu driven. The stack and the queue are printed
after every menu choice so you can see what each one does.


FILES
---------------------------------------------------------------
  sqll.h        Header: node struct, Stack class, Queue class,
                and the prototypes for Task 3 and Task 4
  sqll.cpp      All the function bodies
  main.cpp      Menu driven driver program
  README.txt    This file
  Task5.pdf     Write-up for the deque discussion post
  screenshots/  Screenshots showing the program running


HOW TO COMPILE AND RUN
---------------------------------------------------------------
    g++ main.cpp sqll.cpp -o sqll
    ./sqll

On Windows the file is sqll.exe and you run it with:  sqll.exe


MENU OPTIONS
---------------------------------------------------------------
  1. Push
  2. Pop
  3. Enqueue
  4. Dequeue
  5. Evaluate an expression
  6. Solve Josephus's Problem
  7. Exit


FUNCTIONS
---------------------------------------------------------------
Stack (linked list, top only)

  void push(string &value)                        [Task 1]
      Makes a new node and puts it on top. The old top gets
      linked underneath it.

  string pop()                                    [Task 1]
      Takes the top node off, returns its value and deletes the
      node. Throws if the stack is empty.

  string peek()
      Returns the top value without removing it.

  bool isEmpty()
      True when top is nullptr.

  void display()
      Prints the stack from the top down.

Queue (linked list, front and rear)

  void enqueue(string &value)                     [Task 2]
      Adds a new node at the back. If the queue was empty the
      new node is both the front and the rear.

  string dequeue()                                [Task 2]
      Removes the front node, returns its value and deletes it.
      If that emptied the queue, rear is reset to nullptr too.
      Throws if the queue is empty.

  bool isEmpty()
      True when front is nullptr.

  void display()
      Prints the queue from front to back.

Task 3

  double evaluateExpression(string &expr)
      Dijkstra's two stack algorithm. One stack holds the
      numbers, the other holds the operators.
        "("        is skipped
        + - * / ^  goes on the operator stack
        a number   goes on the number stack
        ")"        pop one operator and two numbers, do the
                   math, push the answer back
      When the tokens run out the answer is the last thing left
      on the number stack.
      Handles + - * / and ^ (exponent). Divide by zero is caught
      and reported instead of crashing.
      The expression has to be fully parenthesized with spaces
      between every token.

Task 4

  void josephus(int n, int k)
      N soldiers in a circle, every kth one is removed until one
      is left. The queue is the circle. Moving someone from the
      front to the back is the same as walking past them, so we
      do that k-1 times and then dequeue the kth one for real.
      Prints the order people are eliminated and who survives.


SAMPLE RUNS
---------------------------------------------------------------
Stack (option 1 and 2) - last in, first out

  Push apple, banana, cherry    Stack: cherry banana apple
  Pop                           Popped: cherry
                                Stack: banana apple

Queue (option 3 and 4) - first in, first out

  Enqueue red, green, blue      Queue: red green blue
  Dequeue                       Dequeued: red
                                Queue: green blue

Expressions (option 5)

  ( 1 + ( 2 * 3 ) )                   Result: 7
  ( ( 1 + 2 ) * ( 9 - 4 ) )           Result: 15
  ( 2 ^ 10 )                          Result: 1024
  ( ( 8 / 2 ) ^ ( 1 + 2 ) )           Result: 64
  ( 1 + ( ( 2 ^ 3 ) - ( 12 / 4 ) ) )  Result: 6
  ( 5 / 0 )                           Could not evaluate that:
                                      Cannot divide by zero

Josephus (option 6)

  n = 7, k = 3    Elimination order: 3 6 2 7 5 1
                  Survivor: soldier 4
  n = 5, k = 2    Elimination order: 2 4 1 5
                  Survivor: soldier 3
  n = 5, k = 1    Elimination order: 1 2 3 4
                  Survivor: soldier 5


NOTES
---------------------------------------------------------------
- Every node made with "new" is freed with "delete". The
  destructors empty the stack and the queue when the program
  ends.
- Compiled and tested with g++ using -Wall and -Wextra, no
  warnings.
- One fix in the base code: option 4 was checking
  stack.isEmpty() before dequeuing. It checks queue.isEmpty()
  now, otherwise dequeue could be called on an empty queue.
- Option 5 is wrapped in a try/catch so a bad expression prints
  a message instead of crashing the program.
