#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

class GraphvizBST {
public:
    static void saveDotFile(const std::string &filename, const std::string &dotContent) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << dotContent;
            outFile.close();
            std::cout << "DOT file saved: " << filename << std::endl;
        } else {
            std::cerr << "Error: Could not open file " << filename << std::endl;
        }
    }

    static std::string generateDot(const Node *root) {
        std::string dot = "digraph BST {\n";
        dot += "    node [fontname=\"Arial\"];\n";
        dot += generateDotHelper(root);
        dot += "}\n";
        return dot;
    }

private:
    static std::string generateDotHelper(const Node *node) {
        if (!node)
            return "";
        std::string result;
        if (node->left) {
            result += "    " + std::to_string(node->data) + " -> " + std::to_string(node->left->data) + " [label=\"L\"];\n";
            result += generateDotHelper(node->left);
        } else {
            std::string nullNode = "nullL" + std::to_string(node->data);
            result += "    " + nullNode + " [shape=point];\n";
            result += "    " + std::to_string(node->data) + " -> " + nullNode + ";\n";
        }
        if (node->right) {
            result += "    " + std::to_string(node->data) + " -> " + std::to_string(node->right->data) + " [label=\"R\"];\n";
            result += generateDotHelper(node->right);
        } else {
            std::string nullNode = "nullR" + std::to_string(node->data);
            result += "    " + nullNode + " [shape=point];\n";
            result += "    " + std::to_string(node->data) + " -> " + nullNode + ";\n";
        }
        return result;
    }
};

class Bst {
    Node *root;

    void _print(Node *subroot) {
        if (!subroot) {
            return;
        } else {
            _print(subroot->left);
            cout << subroot->data << " ";
            _print(subroot->right);
        }
    }
    void _insert(Node *&subroot, int x) {
        if (!subroot) { // if(root == nullptr)
            subroot = new Node(x);
        } else {
            if (x < subroot->data) {
                _insert(subroot->left, x);
            } else {
                _insert(subroot->right, x);
            }
        }
    }

    void _delete(Node *&subroot, int x) {
        /**
         * Deletes a node from the BST.
         * 
         * @param subroot The current subtree to search for the node to delete.
         * @param x The value of the node to delete.
         */
        if (!subroot) {
            // If the tree is empty or the node to delete is not found, return.
            cout << "Number not found" << endl;
            return;
        }
        if (x < subroot->data) {
            // If the value to delete is less than the current node's value, 
            // recursively search in the left subtree.
            _delete(subroot->left, x);
        } else if (x > subroot->data) {
            // If the value to delete is greater than the current node's value, 
            // recursively search in the right subtree.
            _delete(subroot->right, x);
        } else {
            // If the value to delete is found, handle different cases of node deletion.
            if (!subroot->left && !subroot->right) {
                // If the node has no children, simply delete it.
                delete subroot;
                subroot = nullptr;
            } else if (!subroot->left) {
                // If the node has only a right child, replace it with the right child.
                Node *temp = subroot;
                subroot = subroot->right;
                delete temp;
            } else if (!subroot->right) {
                // If the node has only a left child, replace it with the left child.
                Node *temp = subroot;
                subroot = subroot->left;
                delete temp;
            } else {
                // If the node has two children, replace it with its inorder successor.
                Node *temp = subroot->right;
                while (temp->left) {
                    temp = temp->left;
                }
                // Replace the node's value with the inorder successor's value.
                subroot->data = temp->data;
                // Delete the inorder successor from the right subtree.
                _delete(subroot->right, temp->data);
                return;
            }
        }
    }
    int _ipl(Node *root, int depth = 0) {
        if (!root)
            return 0; // Base case: Empty subtree contributes 0 to IPL
        return depth + _ipl(root->left, depth + 1) + _ipl(root->right, depth + 1);
    }

public:
    Bst() { root = nullptr; }
    void insert(int x) { _insert(root, x); }
    bool search(int key) { return 0; }
    void deleteNode(int x) { _delete(root, x); }
    void print() { _print(root); }
    void saveDotFile(const std::string &filename) {
        std::string dotContent = GraphvizBST::generateDot(root);
        GraphvizBST::saveDotFile(filename, dotContent);
    }

    /**
     * Computes the Internal Path Length (IPL) of a Binary Search Tree (BST).
     *
     * Definition:
     * The Internal Path Length (IPL) of a BST is the sum of the depths of all nodes in the tree.
     * The depth of a node is the number of edges from the root to that node.
     *
     * Example:
     *        10
     *       /  \
     *      5    15
     *     / \     \
     *    2   7    20
     *
     * IPL = (depth of 10) + (depth of 5) + (depth of 15) + (depth of 2) + (depth of 7) + (depth of 20)
     *     = 0 + 1 + 1 + 2 + 2 + 2 = 8
     *
     * @param root Pointer to the root node of the BST.
     * @param depth Current depth of the node (default is 0 for the root call).
     * @return The sum of depths of all nodes (Internal Path Length).
     */
    int ipl() {
        return _ipl(root);
    }
};

bool unique_value(int *arr, int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return false;
        }
    }
    return true;
}

int main() {
    // Bst tree;
    // int root = pow(2, 15) / 2;
    // int max = pow(2, 15) - 1;
    // vector<int> arr;
    // arr.push_back(root);
    // tree.insert(root);
    // for (int i = 1; i < 5000; i++) {
    //     int r = rand() % max;
    //     while (!unique_value(arr.data(), arr.size(), r)) {
    //         r = rand() % max;
    //     }
    //     tree.insert(r);
    //     arr.push_back(r);
    // }

    // tree.print();
    // tree.saveDotFile("bst_snapshot.dot");

    Bst tree2;
    // tree2.insert(10);
    // tree2.insert(5);
    // tree2.insert(15);
    // tree2.insert(2);
    // tree2.insert(7);
    // tree2.insert(20);
    // cout << "Internal Path Length: " << tree2.ipl() << endl;

    tree2.print();

    tree2.insert(12);

    cout << "Next \n\n";
    tree2.print();

    cout << "Next \n\n";

    tree2.deleteNode(5);
    tree2.print();

    cout << "Next \n\n";

    tree2.deleteNode(12);
    tree2.print();

    cout << "Next \n\n";
    tree2.deleteNode(12);
    tree2.print();
}