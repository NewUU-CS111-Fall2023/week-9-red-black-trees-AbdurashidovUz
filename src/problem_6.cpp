#include <iostream>
#include <vector>

struct Node {
    int data;
    Node* left;
    Node* right;

    explicit Node(int data)
        : data(data), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;

    int blackHeight(Node* node) {
        if (node == nullptr)
            return 0;

        int leftHeight = blackHeight(node->left);
        int rightHeight = blackHeight(node->right);

        return (node->data % 2 == 0) ? (leftHeight + 1) : (rightHeight + 1);
    }

    void displayBlackHeight(Node* node) {
        if (node == nullptr)
            return;

        displayBlackHeight(node->left);
        std::cout << node->data << " - " << blackHeight(node) << std::endl;
        displayBlackHeight(node->right);
    }

public:
    BinaryTree()
        : root(nullptr) {}

    void insert(int data) {
        Node* newNode = new Node(data);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node* current = root;
        while (true) {
            if (data < current->data) {
                if (current->left == nullptr) {
                    current->left = newNode;
                    break;
                }
                current = current->left;
            } else if (data > current->data) {
                if (current->right == nullptr) {
                    current->right = newNode;
                    break;
                }
                current = current->right;
            } else {
                // Duplicate values are not allowed
                delete newNode;
                break;
            }
        }
    }

    void displayBlackHeight() {
        displayBlackHeight(root);
    }
};

int main() {
    int N;
    std::cin >> N;

    BinaryTree tree;

    for (int i = 0; i < N; i++) {
        int value;
        std::cin >> value;
        tree.insert(value);
    }

    tree.displayBlackHeight();

    return 0;
}
