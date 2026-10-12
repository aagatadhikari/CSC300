#include "bstA.h"

// Commands read from the input file (one per line):
//   0       exit                     7       postorder traversal
//   1 x     insert x (iterative)     8       print tree (sideways)
//   2 x     insert x (recursive)     9 [x]   height of node x (tree height if no x)
//   3 x     search x (iterative)     10      count nodes
//   4 x     search x (recursive)     11      is the tree balanced?
//   5       preorder traversal       12 x    delete x
//   6       inorder traversal        13      BFS (level-order) traversal

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cerr <<"Usage: ./a <filename>" << endl;
        return 1;
    }

    int size = 50;
    string filename = argv[1];

    BST bst(size);

    ifstream infile(filename);

    if(!infile)
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while(getline(infile, line))
    {
        istringstream iss(line);
        int command, data;
        iss >> command;
        
        switch(command) {
            case 0:
                cout << "Exiting ..." << endl;
                return 0;
            case 1:
                iss >> data;
                // insertI() prints its own message for duplicates / no room
                if(bst.insertI(data))
                    cout << "Insert I: " << data << endl;
                break;
            case 2:
                iss >> data;
                // insertR() prints its own message for duplicates / no room
                if(bst.insertR(data))
                    cout << "Insert R: " << data << endl;
                break;
            case 3:
                iss >> data;
                if(bst.searchI(data))
                    cout << data << " found I" << endl;
                else
                    cout << data << " not found I" << endl;
                break;
            case 4:
                iss >> data;
                if(bst.searchR(data))
                    cout << data << " found R" << endl;
                else
                    cout << data << " not found R" << endl;
                break;
            case 5:
                cout << "Preoder traversal: ";
                bst.preorder();
                cout << endl;
                break;
            case 6:
                cout << "Inorder traversal: ";
                bst.inorder();
                cout << endl;
                break;
            case 7:
                cout << "Postorder traversal: ";
                bst.postorder();
                cout << endl;
                break;
            case 8:
                cout << "Binary Search Tree" << endl;
                bst.printTree(0, 0);
                cout << endl;
                break;
            case 9:
                // Task 1: "9 x" -> height of node x, "9" alone -> height of the tree
                if(iss >> data)
                {
                    int h = bst.heightOf(data);
                    if(h == -2)
                        cout << "Height: " << data << " not found" << endl;
                    else
                        cout << "Height of node " << data << ": " << h << endl;
                }
                else
                    cout << "Height of tree: " << bst.height() << endl;
                break;
            case 10:
                // Task 2
                cout << "Total nodes: " << bst.countNodes() << endl;
                break;
            case 11:
                // Task 3
                cout << "Is balanced: " << bst.isBalanced() << endl;
                break;
            case 12:
                // Task 4
                iss >> data;
                if(bst.deleteNode(data))
                    cout << "Deleted: " << data << endl;
                else
                    cout << "Delete: " << data << " not found" << endl;
                break;
            case 13:
                // Task 5
                cout << "BFS traversal:" << endl;
                bst.BFS();
                break;
            default:
                cout << "Invalid command" << endl;
        }
    }

    return 0;
}