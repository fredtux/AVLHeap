#include <iostream>
#include <vector>

/**
 * Recapitulat de aici: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 */

using namespace std;

ostream &operator<<(ostream &out, vector<int> v) {
    for (auto x: v) {
        out << x << " ";
    }
    out << "\n";

    return out;
}

struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
};

inline int height(Node *n) {
    return n == nullptr ? 0 : n->height;
}

Node *newNode(int key) {
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // frunza

    return node;
}

inline int getBalance(Node *n) {
    if (n == nullptr) {
        return 0;
    }

    return height(n->left) - height(n->right);
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

Node *insert(Node *node, int key) {
    // BST
    if (node == nullptr) {
        return newNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    // Actualizare height
    node->height = 1 + max(height(node->left), height(node->right));

    // Balanta
    int balance = getBalance(node);
    // LL
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    // RR
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void preOrder(Node *root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node *root = nullptr;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    preOrder(root);

    return 0;
}