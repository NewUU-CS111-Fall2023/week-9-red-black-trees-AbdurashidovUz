#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    explicit Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left != nullptr)
            rightChild->left->parent = node;

        rightChild->parent = node->parent;

        if (node->parent == nullptr)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;

        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right != nullptr)
            leftChild->right->parent = node;

        leftChild->parent = node->parent;

        if (node->parent == nullptr)
            root = leftChild;
        else if (node == node->parent->left)
            node->parent->left = leftChild;
        else
            node->parent->right = leftChild;

        leftChild->right = node;
        node->parent = leftChild;
    }

    void fixViolation(Node* node) {
        while (node != root && node->color == RED && node->parent->color == RED) {
            Node* parent = node->parent;
            Node* grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    rotateRight(grandparent);
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            } else {
                Node* uncle = grandparent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    rotateLeft(grandparent);
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }

        root->color = BLACK;
    }

    void printTree(Node* node) {
        if (node == nullptr)
            return;

        std::cout << "(";
        if (node->color == RED)
            std::cout << node->data << "(RED)";
        else
            std::cout << node->data << "(BLACK)";

        printTree(node->left);
        printTree(node->right);

        std::cout << ")";
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int data) {
        Node* newNode = new Node(data);
        Node* parent = nullptr;
        Node* current = root;

        while (current != nullptr) {
            parent = current;
            if (data < current->data)
                current = current->left;
            else if (data > current->data)
                current = current->right;
            else {
                // Duplicate values are not allowed in the Red-Black Tree
                delete newNode;
                return;
            }
        }

        newNode->parent = parent;

        if (parent == nullptr)
            root = newNode;
        else if (data < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;

        fixViolation(newNode);
    }

    void printTree() {
        printTree(root);
        std::cout << std::endl;
    }
};

int main() {
    int n;
    std::cin >> n;

    RedBlackTree tree;

    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        tree.insert(value);
    }

    tree.printTree();

    return 0;
}
