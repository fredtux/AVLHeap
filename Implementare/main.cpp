#include <iostream>
#include <vector>

/**
 * Surse de inspiratie
 * https://www.coursehero.com/u/file/9760032/Written-Assignment-2-sample-solution/#question
 * https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 * https://www.geeksforgeeks.org/binary-heap/
 * https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
 *
 */

using namespace std;

struct Node {
    int key;
    int height;
    Node *parent;
    Node *left;
    Node *right;
};

inline int height(Node *n) {
    return n == nullptr ? 0 : n->height;
}

Node *newNode(int key) {
    Node *node = new Node();
    node->key = key;
    node->parent = NULL;
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

    if (x != nullptr) {
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    } else {
        return y;
    }
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

void percolate_down(Node *node) {
    // Frunza
    if ((node->left == nullptr) && (node->right == nullptr)) {
        return;
    }

    // BST
    // Are copil - stanga
    if (node->right == NULL) {
        if (node->key > node->left->key) {
            swap(node->key, node->left->key);
            percolate_down(node->left);
        }

        return;
    }

    // Are copil - dreapta
    if (node->left == NULL) {
        if (node->key > node->right->key) {
            swap(node->key, node->right->key);
            percolate_down(node->right);
        }

        return;
    }

    // Are 2 copii => il alegem pe cel mai mic
    if (node->left->key < node->right->key) {
        // L < R
        if (node->key > node->left->key) {
            swap(node->key, node->left->key);
            percolate_down(node->left);
        }
    } else {
        // L > R
        if (node->key > node->right->key) {
            swap(node->key, node->right->key);
            percolate_down(node->right);
        }
    }
}

Node *avl(Node *node, Node *result, int &key) {
    // Actualizare height
    node->height = 1 + max(height(node->left), height(node->right));

    // Balanta
    int balance = getBalance(node);
    // LL
    if (balance > 1 && key < node->left->key) {
        result = rightRotate(node);
        percolate_down(result);
        return result;
    }
    // RR
    if (balance < -1 && key > node->right->key) {
        result = leftRotate(node);
        percolate_down(result);
        return result;
    }
    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        result = rightRotate(node);
        percolate_down(result);
        return result;
    }
    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        result = leftRotate(node);
        percolate_down(result);
        return result;
    }

    return nullptr;
}

Node *insert(Node *node, int key) {
    Node *result;

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

    percolate_down(node);

    result = avl(node, result, node->key);
    if (result == nullptr)
        return node;
    else
        return result;
}


int extractMin(Node *&root) {
    if (root == nullptr)
        return -0x7FFFFFFF;

    int result = root->key;

    if (root->left == nullptr && root->right == nullptr) {
        root = nullptr;
        return result;
    }


    bool left = true;

    Node *tmp = root;
    Node *tmp2 = tmp;
    while (tmp->left != nullptr || tmp->right != nullptr) {
        if (tmp->left != nullptr) {
            swap(tmp->key, tmp->left->key);
            tmp2 = tmp;
            tmp = tmp->left;
            left = true;
        } else {
            swap(tmp->key, tmp->right->key);
            tmp2 = tmp;
            tmp = tmp->right;
            left = false;
        }
    }

    if (left) {
        tmp2->left = nullptr;
    } else {
        tmp2->right = nullptr;
    }
    delete tmp;

    percolate_down(root);

    int key = root->key;
    Node *result2 = new Node();
    result2 = avl(root, result2, key);
    if (result2 != nullptr)
        root = result2;

    percolate_down(root);

    return result;
}

Node *dfs(Node *root, int &key) {
    if (root == nullptr)
        return nullptr;

    if (root->key == key)
        return root;

    Node *result;
    result = dfs(root->left, key);
    if (result == nullptr)
        return dfs(root->right, key);
    else
        return result;
}

void deleteFromAVLHeap(Node *&root, int key) {
    Node *node = dfs(root, key);

    swap(root->key, node->key);
    extractMin(root);
}

void preOrder(Node *root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void printBT(const string &prefix, const Node *node, bool isLeft, bool isFirst = true) {
    if (node != nullptr) {
        cout << prefix;

        if (isFirst)
            cout << "────";
        else
            cout << (isLeft ? "├──" : "└──");

        cout << node->key << "\n";

        printBT(prefix + (isLeft ? "│   " : "    "), node->left, true, false);
        printBT(prefix + (isLeft ? "│   " : "    "), node->right, false, false);
    }
}

int main() {
    Node *root;

    //// Exemplul 1
    cout << "\n############## EXEMPLUL 1 ##############\n";

    root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    preOrder(root);
    cout << "\n";
    printBT("", root, false);

    cout << "\n\n";

    cout << extractMin(root) << "\n";
    preOrder(root);
    cout << "\n";
    printBT("", root, false);
    cout << "\n\n";

    cout << extractMin(root) << "\n";
    preOrder(root);
    cout << "\n";
    printBT("", root, false);
    cout << "\n\n";

    cout << extractMin(root) << "\n";
    preOrder(root);
    cout << "\n";
    printBT("", root, false);
    cout << "\n\n";

    cout << extractMin(root) << "\n";
    preOrder(root);
    cout << "\n";
    printBT("", root, false);
    cout << "\n\n";

    cout << extractMin(root) << "\n";
    preOrder(root);
    cout << "\n";
    printBT("", root, false);
    cout << "\n\n";


    cout << extractMin(root) << "\n";
    preOrder(root);
    cout << "\n";
    printBT("", root, false);
    cout << "\n\n";

    cout << extractMin(root) << "\n";
    preOrder(root);
    cout << "\n";
    printBT("", root, false);
    cout << "\n\n";


    //// Exemplul 2
    cout << "\n############## EXEMPLUL 2 ##############\n";

    root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    preOrder(root);
    cout << "\n";
    printBT("", root, false);

    cout << "\n\n";

    cout << extractMin(root) << "\n";
    deleteFromAVLHeap(root, 20);
    preOrder(root);
    cout << "\n";
    printBT("", root, false);
    cout << "\n\n";

    cout << extractMin(root) << "\n";
    deleteFromAVLHeap(root, 40);
    preOrder(root);
    cout << "\n";
    printBT("", root, false);
    cout << "\n\n";

    cout << extractMin(root) << "\n";
    preOrder(root);
    cout << "\n";
    printBT("", root, false);
    cout << "\n\n";


    //// Exemplul 3
    cout << "\n############## EXEMPLUL 3 ##############\n";

    root = nullptr;

    root = insert(root, 2);
    root = insert(root, 3);
    root = insert(root, 1);
    preOrder(root);
    cout << "\n";
    printBT("", root, false);

    return 0;
}