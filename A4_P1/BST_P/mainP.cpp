#include "bstP.h"

// Commands read from the input file (one per line):
//   0       exit                 6       postorder traversal
//   1 x     insert x             7       print tree (sideways)
//   2 x     search x             8 [x]   height of node x (tree height if no x)
//   3 x     delete x             9       count nodes
//   4       inorder traversal    10      is the tree balanced?
//   5       preorder traversal   11      BFS (level-order) traversal

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Usage: ./a <filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    BST tree;

    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        int command, data;

        if (!(iss >> command)) {
            cerr << "Invalid command format." << endl;
            continue;
        }

        switch (command) {
            case 0:
                cout << "Exiting...!" << endl;
                return 0;
            case 1:
                if (iss >> data) {
                    // insertNode() now rejects duplicates
                    if (tree.insertNode(tree.root, data))
                        cout << "Insert: " << data << endl;
                    else
                        cout << "Duplicate: " << data << " already in BST, not inserted" << endl;
                } else {
                    cerr << "Invalid insert command." << endl;
                }
                break;
            case 2:
                if (iss >> data) {
                    node* result = tree.searchNode(tree.root, data);
                    cout << (result ? "Found: " + to_string(data) : "Not found") << endl;
                } else {
                    cerr << "Invalid search command." << endl;
                }
                break;
            case 3:
                if (iss >> data) {
                    // only report a deletion if the value was actually there
                    if (tree.searchNode(tree.root, data) == nullptr) {
                        cout << "Delete: " << data << " not found" << endl;
                    } else {
                        tree.deleteNode(tree.root, data);
                        cout << "Deleted: " << data << endl;
                    }
                } else {
                    cerr << "Invalid delete command." << endl;
                }
                break;
            case 4:
                cout << "Inorder traversal: ";
                tree.inorder(tree.root);
                cout << endl;
                break;
            case 5:
                cout << "Preorder traversal: ";
                tree.preorder(tree.root);
                cout << endl;
                break;
            case 6:
                cout << "Postorder traversal: ";
                tree.postorder(tree.root);
                cout << endl;
                break;
            case 7:
                cout << "Binary Search Tree" << endl;
                tree.printTree(tree.root, 0);
                cout << endl;
                break;
            case 8: {
                // Task 1: "8 x" -> height of node x, "8" alone -> height of the tree (root)
                if (iss >> data) {
                    node* target = tree.searchNode(tree.root, data);
                    if (target == nullptr)
                        cout << "Height: " << data << " not found" << endl;
                    else
                        cout << "Height of node " << data << ": " << tree.height(target) << endl;
                } else {
                    cout << "Height of tree: " << tree.height(tree.root) << endl;
                }
                break;
            }
            case 9:
                // Task 2
                cout << "Total nodes: " << tree.countNodes(tree.root) << endl;
                break;
            case 10:
                // Task 3
                cout << "Is balanced: " << tree.isBalanced(tree.root) << endl;
                break;
            case 11:
                // Task 5
                cout << "BFS traversal:" << endl;
                tree.BFS(tree.root);
                break;
            default:
                cerr << "Invalid command." << endl;
        }
    }

    return 0;
}
