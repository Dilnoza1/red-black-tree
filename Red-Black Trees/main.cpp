#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;

    Node(int data) : data(data) {
        left = right = parent = nullptr;
        color = RED;
    }
};

class RedBlackTree {
    Node *root;

    void rotateLeft(Node *&x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;

        else if (x == x->parent->left)
            x->parent->left = y;

        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node *&x) {
        Node *y = x->left;
        x->left = y->right;

        if (y->right != nullptr)
            y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;

        else if (x == x->parent->right)
            x->parent->right = y;

        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    void fixInsertRBTree(Node *&ptr) {
        Node *parent = nullptr;
        Node *grandparent = nullptr;

        while (ptr != root && ptr->color != BLACK && ptr->parent->color == RED) {
            parent = ptr->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node *uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    ptr = grandparent;
                } else {
                    if (ptr == parent->right) {
                        rotateLeft(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }

                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    ptr = parent;
                }
            } else {
                Node *uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    ptr = grandparent;
                } else {
                    if (ptr == parent->left) {
                        rotateRight(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }

                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    ptr = parent;
                }
            }
        }

        root->color = BLACK;
    }

    void inorderBST(Node *&ptr) {
        if (ptr == nullptr)
            return;

        inorderBST(ptr->left);
        cout << ptr->data << " ";
        inorderBST(ptr->right);
    }

public:
    RedBlackTree() {
        root = nullptr;
    }

    void insert(const int &n) {
        Node *node = new Node(n);
        if (root == nullptr) {
            node->color = BLACK;
            root = node;
        } else {
            Node *ptr = root;
            Node *prev = nullptr;
            while (ptr != nullptr) {
                prev = ptr;
                if (node->data < ptr->data)
                    ptr = ptr->left;
                else
                    ptr = ptr->right;
            }

            node->parent = prev;
            if (node->data < prev->data)
                prev->left = node;
            else
                prev->right = node;

            fixInsertRBTree(node);
        }
    }

    void inorder() {
        inorderBST(root);
    }
};

int main() {
    RedBlackTree tree;

    tree.insert(7);
    tree.insert(6);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);

    tree.inorder();

    return 0;
}
