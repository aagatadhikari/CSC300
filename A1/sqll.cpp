#include "sqll.h"

//======================= STACK ===========================

Stack::Stack()
{
    top = nullptr; 
}

Stack::~Stack() 
{
    while (!isEmpty()) 
    {
        pop();
    }
}

/*
 push - Task 1
 Makes a new node and puts it on top of the stack.
 */
void Stack::push(string& value) 
{
    node* newNode = new node(value);

    newNode->next = top;   // old top sits under the new one
    top = newNode;         // new node is the top now
}

/*
 pop - Task 1
 Takes the top node off, gives back its value and frees the node.
 */
string Stack::pop() 
{
    if (isEmpty())
    {
        throw runtime_error("Stack is empty");
    }

    node* temp = top;            // remember the node we are removing
    string value = temp->data;   // grab the value before deleting

    top = top->next;             // move the top down one
    delete temp;

    return value;
}

string Stack::peek() 
{
    if (isEmpty()) 
    {
        throw runtime_error("Stack is empty");
    }

    return top->data;  
}

bool Stack::isEmpty() 
{
    return top == nullptr;
}

void Stack::display()
{
    node* current = top;
    cout << "Stack: ";
    while (current != nullptr) 
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

//======================= QUEUE ===========================

Queue::Queue()
{
    front = nullptr;
    rear = nullptr; 
}

Queue::~Queue() 
{
    while (!isEmpty()) 
    {
        dequeue();
    }
}

/*
 enqueue - Task 2
 Adds a new node at the back of the queue.
 */
void Queue::enqueue(string& value) 
{
    node* newNode = new node(value);

    if (isEmpty())
    {
        // empty queue, so this node is both the front and the back
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;   // hook it on after the old back
        rear = newNode;         // and it becomes the new back
    }
}

/*
 dequeue - Task 2
 Removes the front node, gives back its value and frees the node.
 */
string Queue::dequeue() 
{
    if (isEmpty())
    {
        throw runtime_error("Queue is empty");
    }

    node* temp = front;
    string value = temp->data;

    front = front->next;     // next one in line becomes the front

    if (front == nullptr)
    {
        rear = nullptr;      // queue is empty now, so rear has to reset too
    }

    delete temp;

    return value;
}

bool Queue::isEmpty() 
{
    return front == nullptr;
}

void Queue::display()
{
    node* current = front;
    cout << "Queue: ";
    
    while (current != nullptr) 
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
//======================= DIJKSTRA'S TWO STACK ===========================
/*
 evaluateExpression - Task 3
 Dijkstra's two stack method. One stack keeps the numbers, the other keeps
 the operators. Every time we hit a ")" we do one operation and push the
 answer back on the number stack.
 Expression has to be fully parenthesized with spaces, like: ( 1 + ( 2 * 3 ) )
 */
double evaluateExpression(string& expr) 
{
    Stack ops;    // operators
    Stack vals;   // numbers

    istringstream in(expr);
    string token;

    while (in >> token)
    {
        if (token == "(")
        {
            // nothing to do with a "(", just skip it
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^")
        {
            ops.push(token);
        }
        else if (token == ")")
        {
            // a ")" means we have everything we need for one operation
            string op = ops.pop();
            string second = vals.pop();   // careful, this one is the right side
            string first = vals.pop();

            double right = stod(second);
            double left = stod(first);
            double answer = 0;

            if (op == "+")
            {
                answer = left + right;
            }
            else if (op == "-")
            {
                answer = left - right;
            }
            else if (op == "*")
            {
                answer = left * right;
            }
            else if (op == "/")
            {
                if (right == 0)
                {
                    throw runtime_error("Cannot divide by zero");
                }
                answer = left / right;
            }
            else if (op == "^")
            {
                answer = pow(left, right);
            }

            // push the answer back so it can be used by the next operation
            string result = to_string(answer);
            vals.push(result);
        }
        else
        {
            vals.push(token);   // anything else is a number
        }
    }

    // whatever is left on the number stack is the final answer
    return stod(vals.pop());
}

// ============= JOSEPHUS PROBLEM ===========================
/*
 josephus - Task 4
 N soldiers stand in a circle and every kth one gets removed until only one
 is left. The queue is the circle. Sending someone from the front to the back
 is the same as walking past them.
 */
void josephus(int n, int k) 
{
    if (n <= 0 || k <= 0)
    {
        cout << "n and k both have to be bigger than 0" << endl;
        return;
    }

    Queue circle;

    // put all the soldiers in the queue, 1 to n
    for (int i = 1; i <= n; i++)
    {
        string soldier = to_string(i);
        circle.enqueue(soldier);
    }

    cout << "Elimination order: ";

    while (!circle.isEmpty())
    {
        // skip k-1 soldiers by moving them to the back of the queue
        for (int i = 1; i < k; i++)
        {
            string skipped = circle.dequeue();
            circle.enqueue(skipped);
        }

        // the one at the front now is the kth one, so he is out
        string out = circle.dequeue();

        if (circle.isEmpty())
        {
            // last one standing
            cout << endl;
            cout << "Survivor: soldier " << out << endl;
        }
        else
        {
            cout << out << " ";
        }
    }
}
