#include <iostream>
#include <vector>

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

    void deleteFix(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;

                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }

                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }

                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;

                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }

                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }

                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }

        x->color = BLACK;
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

    void deleteNode(int data) {
        Node* z = root;
        Node* x, * y;
        while (z != nil) {
            if (z->data == data)
                break;

            if (data < z->data)
                z = z->left;
            else
                z = z->right;
        }

        if (z == nil)
            return;

        y = z;
        Color yOriginalColor = y->color;

        if (z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;

            if (y->parent == z)
                x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        if (yOriginalColor == BLACK)
            deleteFix(x);

        delete z;
    }

    Node* minimum(Node* node) {
        while (node->left != nil)
            node = node->left;

        return node;
    }

    void inorderTraversal(Node* node, std::vector<int>& inorder) {
        if (node != nil) {
            inorderTraversal(node->left, inorder);
            inorder.push_back(node->data);
            inorderTraversal(node->right, inorder);
        }
    }

    std::vector<int> inorderTraversal() {
        std::vector<int> inorder;
        inorderTraversal(root, inorder);
        return inorder;
    }
};

int main() {
    int N;
    std::cin >> N;

    RedBlackTree tree;

    std::vector<int> values(N);
    for (int i = 0; i < N; i++)
        std::cin >> values[i];

    for (int i = 0; i < N; i++)
        tree.insert(values[i]);

    std::vector<int> sorted = tree.inorderTraversal();

    std::cout << "Inorder Traversal: ";
    for (int i = 0; i < sorted.size(); i++)
        std::cout << sorted[i] << " ";
    std::cout << std::endl;

    // Example usage of deleteNode()
    tree.deleteNode(5);

    sorted = tree.inorderTraversal();

    std::cout << "Inorder Traversal after deletion: ";
    for (int i = 0; i < sorted.size(); i++)
        std::cout << sorted[i] << " ";
    std::cout << std::endl;

    return 0;
}
