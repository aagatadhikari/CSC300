#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

using namespace std;

// ---------------------------------------------------------------------------
// Custom linked-list queue (FIFO), reused from the earlier queue assignment.
// It is a template so the same code can store node pointers (BST_P) or array
// indices (BST_A). No STL containers are used.
// ---------------------------------------------------------------------------

template <typename T>
struct QNode
{
    T data;          // value stored in this queue node
    QNode<T>* next;  // link to the node behind it in the line

    QNode(T value) : data(value), next(nullptr) {}
};

template <typename T>
class Queue
{
    private:
        QNode<T>* frontPtr;  // first element (next to be dequeued)
        QNode<T>* rearPtr;   // last element (most recently enqueued)
        int count;           // number of elements currently in the queue

    public:
        Queue() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}

        // Free every node that is still in the queue
        ~Queue()
        {
            while (!isEmpty())
                dequeue();
        }

        bool isEmpty() const { return frontPtr == nullptr; }
        int size() const { return count; }

        // Add a value to the rear of the queue - O(1)
        void enqueue(T value)
        {
            QNode<T>* newNode = new QNode<T>(value);
            if (isEmpty())
            {
                frontPtr = rearPtr = newNode;
            }
            else
            {
                rearPtr->next = newNode;
                rearPtr = newNode;
            }
            count++;
        }

        // Remove and return the value at the front of the queue - O(1)
        // Caller must check isEmpty() first.
        T dequeue()
        {
            if (isEmpty())
            {
                cerr << "Queue underflow: dequeue on empty queue" << endl;
                return T();
            }
            QNode<T>* temp = frontPtr;
            T value = temp->data;
            frontPtr = frontPtr->next;
            if (frontPtr == nullptr)   // queue became empty
                rearPtr = nullptr;
            delete temp;
            count--;
            return value;
        }

        // Look at the front value without removing it
        T peek() const
        {
            if (isEmpty())
            {
                cerr << "Queue is empty: nothing to peek" << endl;
                return T();
            }
            return frontPtr->data;
        }
};

#endif
