#include <iostream>
#include <string>
using namespace std;

class dict {
private:
    struct Node {
        string s1; // keyword
        string s2; // meaning
        Node* left;
        Node* right;
    };
    Node* root;

public:
    dict() {
        root = NULL;
    }

    void input();
    void create_root(Node*& tree, Node* node);
    void input_display();
    void display(Node* tree);
    void input_remove();
    Node* remove(Node* tree, const string& s);
    Node* findmin(Node* tree);
    void input_find();
    Node* find(Node* tree, const string& s);
    void input_update();
    Node* update(Node* tree, const string& s);
};

// Input a new word
void dict::input() {
    Node* node = new Node;
    cout << "\nEnter the keyword: ";
    cin >> node->s1;
    cout << "Enter the meaning of the keyword: ";
    cin.ignore();
    getline(cin, node->s2);
    create_root(root, node);
}

// Recursive insertion
void dict::create_root(Node*& tree, Node* node) {
    if (tree == NULL) {
        tree = node;
        tree->left = tree->right = NULL;
        cout << "Word inserted successfully!\n";
        return;
    }
    if (node->s1 < tree->s1) {
        create_root(tree->left, node);
    } else if (node->s1 > tree->s1) {
        create_root(tree->right, node);
    } else {
        cout << "The word already exists in the dictionary.\n";
        delete node; // Avoid memory leak
    }
}

// Display the full dictionary
void dict::input_display() {
    if (root != NULL) {
        cout << "\nWords in the dictionary:\n";
        display(root);
    } else {
        cout << "\nThe dictionary is empty.\n";
    }
}

void dict::display(Node* tree) {
    if (tree != NULL) {
        display(tree->left);
        cout << tree->s1 << " = " << tree->s2 << "\n";
        display(tree->right);
    }
}

// Remove a word
void dict::input_remove() {
    if (root != NULL) {
        string s;
        cout << "\nEnter the keyword to delete: ";
        cin >> s;
        root = remove(root, s);
    } else {
        cout << "\nThe dictionary is empty.\n";
    }
}

dict::Node* dict::remove(Node* tree, const string& s) {
    if (tree == NULL) {
        cout << "Word not found.\n";
        return NULL;
    }

    if (s < tree->s1) {
        tree->left = remove(tree->left, s);
    } else if (s > tree->s1) {
        tree->right = remove(tree->right, s);
    } else {
        // Node with one or no child
        if (tree->left == NULL) {
            Node* temp = tree->right;
            delete tree;
            cout << "Word deleted successfully.\n";
            return temp;
        } else if (tree->right == NULL) {
            Node* temp = tree->left;
            delete tree;
            cout << "Word deleted successfully.\n";
            return temp;
        }

        // Node with two children
        Node* temp = findmin(tree->right);
        tree->s1 = temp->s1;
        tree->s2 = temp->s2;
        tree->right = remove(tree->right, temp->s1);
    }
    return tree;
}

dict::Node* dict::findmin(Node* tree) {
    while (tree && tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}

// Search for a word
void dict::input_find() {
    if (root != NULL) {
        string s;
        cout << "\nEnter the keyword to search: ";
        cin >> s;
        find(root, s);
    } else {
        cout << "\nThe dictionary is empty.\n";
    }
}

dict::Node* dict::find(Node* tree, const string& s) {
    if (tree == NULL) {
        cout << "Word not found.\n";
        return NULL;
    }
    if (s == tree->s1) {
        cout << "Found: " << tree->s1 << " = " << tree->s2 << "\n";
        return tree;
    } else if (s < tree->s1) {
        return find(tree->left, s);
    } else {
        return find(tree->right, s);
    }
}

// Update the meaning of a word
void dict::input_update() {
    if (root != NULL) {
        string s;
        cout << "\nEnter the keyword to update: ";
        cin >> s;
        Node* node = update(root, s);
        if (node != NULL) {
            cout << "Enter the new meaning: ";
            cin.ignore();
            getline(cin, node->s2);
            cout << "Word updated successfully!\n";
        }
    } else {
        cout << "\nThe dictionary is empty.\n";
    }
}

dict::Node* dict::update(Node* tree, const string& s) {
    if (tree == NULL) {
        cout << "Word not found.\n";
        return NULL;
    }
    if (s == tree->s1) {
        return tree;
    } else if (s < tree->s1) {
        return update(tree->left, s);
    } else {
        return update(tree->right, s);
    }
}

// Main function
int main() {
    dict d;
    int ch;
    do {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Insert Word\n";
        cout << "2. Display Dictionary\n";
        cout << "3. Remove Word\n";
        cout << "4. Find Word\n";
        cout << "5. Update Meaning\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                d.input();
                break;
            case 2:
                d.input_display();
                break;
            case 3:
                d.input_remove();
                break;
            case 4:
                d.input_find();
                break;
            case 5:
                d.input_update();
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (ch != 6);

    return 0;
}
