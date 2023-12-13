#include <iostream>
#include <vector>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    explicit Node(int data)
        : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;
    Node* nil;

    void leftRotate(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left != nil)
            rightChild->left->parent = node;

        rightChild->parent = node->parent;

        if (node->parent == nil)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;

        rightChild->left = node;
        node->parent = rightChild;
    }

    void rightRotate(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right != nil)
            leftChild->right->parent = node;

        leftChild->parent = node->parent;

        if (node->parent == nil)
            root = leftChild;
        else if (node == node->parent->left)
            node->parent->left = leftChild;
        else
            node->parent->right = leftChild;

        leftChild->right = node;
        node->parent = leftChild;
    }

    void fixInsertion(Node* node) {
        while (node != root && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;

                if (uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            } else {
                Node* uncle = node->parent->parent->left;

                if (uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }
        }

        root->color = BLACK;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nil)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        v->parent = u->parent;
    }

public:
    explicit RedBlackTree() {
        nil = new Node(0);
        nil->color = BLACK;
        root = nil;
    }

    void insert(int data) {
        Node* newNode = new Node(data);
        Node* y = nil;
        Node* x = root;

        while (x != nil) {
            y = x;

            if (newNode->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        newNode->parent = y;

        if (y == nil)
            root = newNode;
        else if (newNode->data < y->data)
            y->left = newNode;
        else
            y->right = newNode;

        newNode->left = nil;
        newNode->right = nil;
        newNode->color = RED;

        fixInsertion(newNode);
    }

    void printTree(Node* node) {
        if (node == nil)
            return;

        printTree(node->right);
        std::cout << node->data << " ";
        printTree(node->left);
    }

    void printTree() {
        printTree(root);
    }
};

intint main() {
    int N;
    std::cin >> N;

    RedBlackTree tree;

    for (int i = 0; i < N; i++) {
        int value;
        std::cin >> value;
        tree.insert(value);
    }

    tree.printTree();
    std::cout << std::endl;

    return 0;
}
