#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* left;
    Node* right;

    // Constructor to create a new node
    Node(int key) {
        value = key;
        left = right = nullptr;
    }
};

class BinarySearchTree {
public:
    Node* root;

    // Constructor to initialize an empty tree
    BinarySearchTree() {
        root = nullptr;
    }

    // Destructor to deallocate memory
    ~BinarySearchTree() {
        destroyTree(root);
    }

    // Recursive function to deallocate nodes
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    // Insert a new node in the BST
    Node* insert(Node* root, int key) {
        if (root == nullptr) {
            return new Node(key);
        }
        if (key < root->value) {
            root->left = insert(root->left, key);
        } else {
            root->right = insert(root->right, key);
        }
        return root;
    }

    // Find the minimum value node in the BST
    int findMin(Node* root) {
        if (root == nullptr) {
            throw runtime_error("Cannot find minimum in an empty tree.");
        }
        Node* current = root;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current->value;
    }

    // Search for a value in the BST
    bool search(Node* root, int key) {
        if (root == nullptr) {
            return false;
        }
        if (root->value == key) {
            return true;
        }
        if (key < root->value) {
            return search(root->left, key);
        }
        return search(root->right, key);
    }

    // Inorder traversal to print the tree
    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->value << " ";
            inorder(root->right);
        }
    }

    // Helper functions
    void insert(int key) {
        root = insert(root, key);
    }

    bool search(int key) {
        return search(root, key);
    }

    int findMin() {
        return findMin(root);
    }

    void printTree() {
        if (root == nullptr) {
            cout << "The tree is empty.\n";
        } else {
            cout << "Tree (in inorder traversal): ";
            inorder(root);
            cout << endl;
        }
    }

    void displayMenu() {
        cout << "\n--- Binary Search Tree Menu ---\n";
        cout << "1. Insert a new value\n";
        cout << "2. Find the minimum value in the tree\n";
        cout << "3. Search for a value in the tree\n";
        cout << "4. Print the tree\n";
        cout << "5. Exit\n";
        cout << "Please select an option (1-5): ";
    }
};

// Main function
int main() {
    BinarySearchTree bst;
    int choice, value;

    cout << "Welcome to the Binary Search Tree Program!" << endl;

    while (true) {
        bst.displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter a value to insert: ";
                cin >> value;
                bst.insert(value);
                cout << "Value " << value << " inserted successfully!\n";
                break;
            case 2:
                try {
                    cout << "The minimum value in the tree is: " << bst.findMin() << endl;
                } catch (runtime_error& e) {
                    cout << e.what() << endl;
                }
                break;
            case 3:
                cout << "Enter a value to search for: ";
                cin >> value;
                if (bst.search(value)) {
                    cout << "Value " << value << " found in the tree!\n";
                } else {
                    cout << "Value " << value << " not found in the tree.\n";
                }
                break;
            case 4:
                bst.printTree();
                break;
            case 5:
                cout << "Exiting the program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please select a valid option (1-5).\n";
        }
    }

    return 0;
}
