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

    Node* insertNode(Node* node, int data) {
        if (node == nullptr)
            return new Node(data);

        if (data < node->data)
            node->left = insertNode(node->left, data);
        else if (data > node->data)
            node->right = insertNode(node->right, data);

        return node;
    }

    int countChildren(Node* node) {
        if (node == nullptr)
            return 0;

        int count = 0;
        if (node->left != nullptr)
            count++;
        if (node->right != nullptr)
            count++;

        return count;
    }

    void displayChildrenCount(Node* node) {
        if (node == nullptr)
            return;

        displayChildrenCount(node->left);
        std::cout << node->data << " - " << countChildren(node) << std::endl;
        displayChildrenCount(node->right);
    }

public:
    BinaryTree()
        : root(nullptr) {}

    void insert(int data) {
        root = insertNode(root, data);
    }

    void displayChildrenCount() {
        displayChildrenCount(root);
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

    tree.displayChildrenCount();

    return 0;
}
