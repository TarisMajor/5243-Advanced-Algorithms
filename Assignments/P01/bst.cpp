#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int x)
    {
        data = x;
        left = right = nullptr;
    }
};

class GraphvizBST
{
public:
    static void saveDotFile(const std::string &filename, const std::string &dotContent)
    {
        std::ofstream outFile(filename);
        if (outFile.is_open())
        {
            outFile << dotContent;
            outFile.close();
            std::cout << "DOT file saved: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error: Could not open file " << filename << std::endl;
        }
    }

    static std::string generateDot(const Node *root)
    {
        std::string dot = "digraph BST {\n";
        dot += "    node [fontname=\"Arial\"];\n";
        dot += generateDotHelper(root);
        dot += "}\n";
        return dot;
    }

private:
    static std::string generateDotHelper(const Node *node)
    {
        if (!node)
            return "";
        std::string result;
        if (node->left)
        {
            result += "    " + std::to_string(node->data) + " -> " + std::to_string(node->left->data) + " [label=\"L\"];\n";
            result += generateDotHelper(node->left);
        }
        else
        {
            std::string nullNode = "nullL" + std::to_string(node->data);
            result += "    " + nullNode + " [shape=point];\n";
            result += "    " + std::to_string(node->data) + " -> " + nullNode + ";\n";
        }
        if (node->right)
        {
            result += "    " + std::to_string(node->data) + " -> " + std::to_string(node->right->data) + " [label=\"R\"];\n";
            result += generateDotHelper(node->right);
        }
        else
        {
            std::string nullNode = "nullR" + std::to_string(node->data);
            result += "    " + nullNode + " [shape=point];\n";
            result += "    " + std::to_string(node->data) + " -> " + nullNode + ";\n";
        }
        return result;
    }
};

class Bst
{
    Node *root;

    void _print(Node *subroot)
    {
        if (!subroot)
        {
            return;
        }
        else
        {
            _print(subroot->left);
            cout << subroot->data << " ";
            _print(subroot->right);
        }
    }
    void _insert(Node *&subroot, int x)
    {
        if (!subroot)
        { // if(root == nullptr)
            subroot = new Node(x);
        }
        else
        {
            if (x < subroot->data)
            {
                _insert(subroot->left, x);
            }
            else
            {
                _insert(subroot->right, x);
            }
        }
    }

    void _delete(Node *&subroot, int x)
    {
        /**
         * Deletes a node from the BST.
         *
         * @param subroot The current subtree to search for the node to delete.
         * @param x The value of the node to delete.
         */
        if (!subroot)
        {
            // If the tree is empty or the node to delete is not found, return.
            cout << "Number not found" << endl;
            return;
        }
        if (x < subroot->data)
        {
            // If the value to delete is less than the current node's value,
            // recursively search in the left subtree.
            _delete(subroot->left, x);
        }
        else if (x > subroot->data)
        {
            // If the value to delete is greater than the current node's value,
            // recursively search in the right subtree.
            _delete(subroot->right, x);
        }
        else
        {
            // If the value to delete is found, handle different cases of node deletion.
            if (!subroot->left && !subroot->right)
            {
                // If the node has no children, simply delete it.
                delete subroot;
                subroot = nullptr;
            }
            else if (!subroot->left)
            {
                // If the node has only a right child, replace it with the right child.
                Node *temp = subroot;
                subroot = subroot->right;
                delete temp;
            }
            else if (!subroot->right)
            {
                // If the node has only a left child, replace it with the left child.
                Node *temp = subroot;
                subroot = subroot->left;
                delete temp;
            }
            else
            {
                // If the node has two children, replace it with its inorder successor.
                Node *temp = subroot->right;
                while (temp->left)
                {
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
    int _ipl(Node *root, int depth = 0)
    {
        if (!root)
            return 0; // Base case: Empty subtree contributes 0 to IPL
        if (!root->left && !root->right)
        {                     // If the node is a leaf node
            return depth - 2; // Subtract 2 from the depth
        }
        return depth + _ipl(root->left, depth + 1) + _ipl(root->right, depth + 1);
    }

    bool _unique_value(int *arr, int n, int x)
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i] == x)
            {
                return false;
            }
        }
        return true;
    }

    int accumulator = 0;
    int _delete_asymmetric(Node *&subroot, int random_Node, vector<int> *&arr, int &accumulator)
    {
        accumulator = 0;

        if (!subroot)
        {
            return accumulator;
        }

        if (subroot->data < random_Node)
        {
            _delete_asymmetric(subroot->right, random_Node, arr, accumulator);
        }
        else if (subroot->data > random_Node)
        {
            _delete_asymmetric(subroot->left, random_Node, arr, accumulator);
        }
        else
        {
            if (!subroot->right)
            {
                _delete(subroot, random_Node);
                accumulator++;
                cout << "Deleted: " << random_Node << endl;
                arr->erase(remove(arr->begin(), arr->end(), random_Node));
                return accumulator;
            }
            else
            {
                _delete_asymmetric(subroot->right, subroot->right->data, arr, accumulator);
                _delete(subroot, random_Node);
                accumulator++;
                cout << "Deleted: " << random_Node << endl;
                arr->erase(remove(arr->begin(), arr->end(), random_Node));
                return accumulator;
            }
        }
        return accumulator;
    }

    void _delete_symmetric(Node *&subroot, int random_Node, vector<int> *&arr)
    {
        accumulator = 0;
        
        int max = pow(2, 15) - 1;
        int r = rand() % max;

        if (!subroot)
        {
            return;
        }

        if (subroot->data < random_Node)
        {
            _delete_symmetric(subroot->right, random_Node, arr);
        }
        else if (subroot->data > random_Node)
        {
            _delete_symmetric(subroot->left, random_Node, arr);
        }
        else
        {
            if (!subroot->right)
            {
                _delete(subroot, random_Node);
                cout << "Deleted1: " << random_Node << endl;
                arr->erase(remove(arr->begin(), arr->end(), random_Node));
                
                while (!_unique_value(arr->data(), arr->size(), r))
                {
                    r = rand() % max;
                }
                insert(r);
                cout << "Inserted1: " << r << endl;
                arr->push_back(r);
                return;
            }
            else
            {
                _delete_symmetric(subroot->right, subroot->right->data, arr);
                _delete(subroot, random_Node);
                accumulator++;
                cout << "Deleted2: " << random_Node << endl;
                arr->erase(remove(arr->begin(), arr->end(), random_Node));

                while (!_unique_value(arr->data(), arr->size(), r))
                {
                    r = rand() % max;
                }
                insert(r);
                cout << "Inserted2: " << r << endl;
                arr->push_back(r);
                return;
            }
        }
        return;
    }
    void _asymmetric(int random_Node, vector<int> *&arr)
    {

        int max = pow(2, 15) - 1;

        int accumulate = _delete_asymmetric(root, random_Node, arr, accumulator);

        cout << accumulate << endl;

        for (int i = 0; i < accumulate; i++)
        {
            int r = rand() % max;
            while (!_unique_value(arr->data(), arr->size(), r))
            {
                r = rand() % max;
            }
            insert(r);
            cout << "Inserted: " << r << endl;
            arr->push_back(r);
        }
    }

public:
    Bst() { root = nullptr; }
    void insert(int x) { _insert(root, x); }
    bool search(int key) { return 0; }
    void deleteNode(int x) { _delete(root, x); }
    void print() { _print(root); }
    void saveDotFile(const std::string &filename)
    {
        std::string dotContent = GraphvizBST::generateDot(root);
        GraphvizBST::saveDotFile(filename, dotContent);
    }

    void delete_asymmetric(vector<int> *arr)
    {

        int size = arr->size();
        int randomNode_place = rand() % size + 1;
        int randomNode = arr->at(randomNode_place);
        _asymmetric(randomNode, arr);
    }

    void delete_symmetric(vector<int> *arr)
    {
        int size = arr->size();
        int randomNode_place = rand() % size + 1;
        int randomNode = arr->at(randomNode_place);
        _delete_symmetric(root, randomNode, arr);
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
    int ipl()
    {
        return _ipl(root);
    }
};

bool unique_value(int *arr, int n, int x)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    Bst tree64, tree128, tree256, tree512, tree1024, tree2048;

    int root = pow(2, 15) / 2;
    int max = pow(2, 15) - 1;
    vector<int> arr64, arr128, arr256, arr512, arr1024, arr2048;
    arr64.push_back(root);
    arr128.push_back(root);
    arr256.push_back(root);
    arr512.push_back(root);
    arr1024.push_back(root);
    arr2048.push_back(root);
    tree64.insert(root);
    tree128.insert(root);
    tree256.insert(root);
    tree512.insert(root);
    tree1024.insert(root);
    tree2048.insert(root);

    for (int i = 1; i < 64; i++)
    {
        int r = rand() % max;
        while (!unique_value(arr64.data(), arr64.size(), r))
        {
            r = rand() % max;
        }
        tree64.insert(r);
        arr64.push_back(r);
    }

    cout << "Internal Path Length: " << tree64.ipl() << endl;
    tree64.saveDotFile("bst64_snapshot.dot");

    // for (int i = 1; i < 60; i++)
    // {
    //     tree64.delete_asymmetric(&arr64);
    // }
    for(int i = 0; i < 30; i++) 
    {
        tree64.delete_symmetric(&arr64);   
        cout << "Out" << endl; 
    }
    

    cout << "Size of arr64: " << arr64.size() << endl;

    cout << "Internal Path Length: " << tree64.ipl() << endl;
    tree64.saveDotFile("bst64_D_snapshot.dot");

    // for( int i = 1; i < 128; i++) {
    //     int r = rand() % max;
    //     while (!unique_value(arr128.data(), arr128.size(), r)) {
    //         r = rand() % max;
    //     }
    //     tree128.insert(r);
    //     arr128.push_back(r);
    // }

    // cout << "Internal Path Length: " << tree128.ipl() << endl;
    // tree128.saveDotFile("bst128_snapshot.dot");

    // Bst tree2;
    // tree2.insert(10);
    // tree2.insert(5);
    // tree2.insert(15);
    // tree2.insert(2);
    // tree2.insert(7);
    // tree2.insert(20);
    // tree2.print();
    // cout << "Internal Path Length: " << tree2.ipl() << endl;
    // tree2.saveDotFile("bst_snapshot.dot");

    // tree2.print();

    // tree2.insert(12);

    // cout << "Next \n\n";
    // tree2.print();

    // cout << "Next \n\n";

    // tree2.deleteNode(5);
    // tree2.print();

    // cout << "Next \n\n";

    // tree2.deleteNode(12);
    // tree2.print();

    // cout << "Next \n\n";
    // tree2.deleteNode(12);
    // tree2.print();
}