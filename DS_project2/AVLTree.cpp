#include "AVLTree.h"
using namespace std;

// Helper function to calculate height
int getHeight(AVLNode* node) {
    if (node == nullptr) return 0;
    return max(getHeight(node->getLeft()), getHeight(node->getRight())) + 1;
}

// Helper function to update balance factor
int getBalanceFactor(AVLNode* node) {
    if (node == nullptr) return 0;
    return getHeight(node->getLeft()) - getHeight(node->getRight());
}

// Right Rotation
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->getLeft();
    AVLNode* T2 = x->getRight();

    // Rotation
    x->setRight(y);
    y->setLeft(T2);

    return x; // New root
}

// Left Rotation
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->getRight();
    AVLNode* T2 = y->getLeft();

    // Rotation
    y->setLeft(x);
    x->setRight(T2);

    return y; // New root
}

// Recursive insertion with balancing
AVLNode* insertNode(AVLNode* node, FlightData* pFlightData) {
    if (node == nullptr) { // Insert new node
        AVLNode* newNode = new AVLNode();
        newNode->setFlightData(pFlightData);
        return newNode;
    }

    string key = pFlightData->GetFlightNumber();
    string nodeKey = node->getFlightData()->GetFlightNumber();

    // Insert into the left or right subtree
    if (key < nodeKey) {
        node->setLeft(insertNode(node->getLeft(), pFlightData));
    }
    else if (key > nodeKey) {
        node->setRight(insertNode(node->getRight(), pFlightData));
    }
    else {
        // Duplicate keys are not allowed in AVL Tree
        return node;
    }

    // Update balance factor
    node->setBF(getBalanceFactor(node));

    // Check balance and perform rotations
    int balance = node->getBF();

    // Left Left Case
    if (balance > 1 && key < node->getLeft()->getFlightData()->GetFlightNumber()) {
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->getRight()->getFlightData()->GetFlightNumber()) {
        return rotateLeft(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->getLeft()->getFlightData()->GetFlightNumber()) {
        node->setLeft(rotateLeft(node->getLeft()));
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->getRight()->getFlightData()->GetFlightNumber()) {
        node->setRight(rotateRight(node->getRight()));
        return rotateLeft(node);
    }

    return node; // Return the unchanged node
}

// Insert function for AVL Tree
bool AVLTree::Insert(FlightData* pFlightData) {
    if (pFlightData->GetNumberofSeats() != 0) return false; // Only add if seats are 0

    root = insertNode(root, pFlightData);
    return true;
}

// Recursive search function
FlightData* searchNode(AVLNode* node, const string& name) {
    if (node == nullptr) return nullptr;

    string nodeKey = node->getFlightData()->GetFlightNumber();
    if (name == nodeKey) {
        return node->getFlightData();
    }
    else if (name < nodeKey) {
        return searchNode(node->getLeft(), name);
    }
    else {
        return searchNode(node->getRight(), name);
    }
}

// Search function for AVL Tree
FlightData* AVLTree::Search(string name) {
    return searchNode(root, name);
}

// Traverse the tree and store elements in the vector
void inorderTraversal(AVLNode* node, vector<FlightData*>& v) {
    if (node == nullptr) return;
    inorderTraversal(node->getLeft(), v);
    v.push_back(node->getFlightData());
    inorderTraversal(node->getRight(), v);
}

// Get all elements in a sorted order
void AVLTree::GetVector(vector<FlightData*>& v) {
    v.clear();
    inorderTraversal(root, v);
}
