#include "SubtitleBST.h"
#include "SubtitleListNode.h"

#include <iostream>
#include <fstream>


// Constructor: initializes the root of the binary search tree (BST) to nullptr
SubtitleBST::SubtitleBST() : root(nullptr) {}

// Destructor: calls the DestroyTree function to deallocate memory for all nodes
SubtitleBST::~SubtitleBST(){
	DestroyTree(root);
}

// Recursive function to delete all nodes in the tree
void SubtitleBST::DestroyTree(SubtitleBSTNode* node) {
    if (node != nullptr) {
        DestroyTree(node->getLeft());
        DestroyTree(node->getRight());
        delete node;
    }
}

// Returns the root node of the tree
SubtitleBSTNode* SubtitleBST::getRoot()  {
	return root;
}

// Insert function to add new subtitle data into the tree
void SubtitleBST::Insert(string time, string content) {
    root = InsertNode(root, time, content);
}

// Recursive function to insert nodes into the tree based on time
SubtitleBSTNode* SubtitleBST::InsertNode(SubtitleBSTNode* node, string time, string content) {
    if (node == nullptr) {
        SubtitleBSTNode* newNode = new SubtitleBSTNode(time, content); // Create new node

        newNode->setTime(time);
        newNode->setContent(content);
        
        return newNode;
    }

    // Insert into left subtree if the new node's time is less than the current node's time
    if (time < node->getTime()) {
        node->setLeft(InsertNode(node->getLeft(), time, content));
    }
    // Insert into right subtree if the new node's time is greater than the current node's time
    else {
        node->setRight(InsertNode(node->getRight(), time, content));
    }
    return node;
}

// Find nodes within a specific time range and link them into a SubtitleListNode
bool SubtitleBST::FindNodesInRange(string startTime, string endTime, SubtitleListNode*& contentHead, SubtitleListNode*& lastContentNode) {
    return FindNodesInRangeHelper(root, startTime, endTime, contentHead, lastContentNode);
}

// Recursive helper function to search the tree and link nodes within a time range
bool SubtitleBST::FindNodesInRangeHelper(SubtitleBSTNode* node, string startTime, string endTime, SubtitleListNode*& contentHead, SubtitleListNode*& lastContentNode) {
    if (node == nullptr) {
        return false;
    }

    bool found = false;

    // Search the left subtree
    if (startTime <= node->getTime()) {
        found = FindNodesInRangeHelper(node->getLeft(), startTime, endTime, contentHead, lastContentNode) || found;
    }

    // If the current node is within the time range, add it to the linked list
    if (startTime <= node->getTime() && node->getTime() <= endTime) {
        SubtitleListNode* newNode = new SubtitleListNode(node->getTime(), node->getContent());
        if (contentHead == nullptr) {
            contentHead = newNode;
        }
        else {
            lastContentNode->setNext(newNode);
        }
        lastContentNode = newNode;
        found = true;
    }

    // Search the right subtree
    if (endTime >= node->getTime()) {
        found = FindNodesInRangeHelper(node->getRight(), startTime, endTime, contentHead, lastContentNode) || found;
    }

    return found;
}

// Print function that initiates in-order traversal of the tree
void SubtitleBST::Print(ofstream& flog) {
    InOrderPrint(root, flog);
}

// Recursive in-order traversal to print the tree contents in sorted order
void SubtitleBST::InOrderPrint(SubtitleBSTNode* node, ofstream& flog) {
    if (node == nullptr) return;

    // Traverse left subtree, print current node, then traverse right subtree
    InOrderPrint(node->getLeft(), flog);
    flog << node->getTime() << " - " << node->getContent() << endl;
    InOrderPrint(node->getRight(), flog);
}

// Search function to find a node based on its time
SubtitleBSTNode* SubtitleBST::Search(string time) {
    return SearchNode(root, time);
}

// Recursive function to search for a node by its time
SubtitleBSTNode* SubtitleBST::SearchNode(SubtitleBSTNode* node, string time) {
    if (node == nullptr || node->getTime() == time) {
        return node;
    }

    // Search the left subtree if the target time is less than the current node's time
    if (time < node->getTime()) {
        return SearchNode(node->getLeft(), time);
    }
    // Search the right subtree if the target time is greater than the current node's time
    else {
        return SearchNode(node->getRight(), time);
    }
}

// Delete function to remove a node from the tree based on its time
void SubtitleBST::Delete(string time) {
    root = DeleteNode(root, time);
}

// Recursive function to delete a node from the tree
SubtitleBSTNode* SubtitleBST::DeleteNode(SubtitleBSTNode* node, string time) {
    if (node == nullptr) return node;

    // Traverse left or right subtree based on the target time
    if (time < node->getTime()) {
        node->setLeft(DeleteNode(node->getLeft(), time));
    }
    else if (time > node->getTime()) {
        node->setRight(DeleteNode(node->getRight(), time));
    }
    else {
        // Case 1: Node has only right child
        if (node->getLeft() == nullptr) {
            SubtitleBSTNode* temp = node->getRight();
            delete node;
            return temp;
        }
        // Case 2: Node has only left child
        else if (node->getRight() == nullptr) {
            SubtitleBSTNode* temp = node->getLeft();
            delete node;
            return temp;
        }

        // Case 3: Node has two children, find the minimum in the right subtree
        SubtitleBSTNode* temp = FindMin(node->getRight());

        // Replace current node with the minimum node from the right subtree
        node->setTime(temp->getTime());
        node->setContent(temp->getContent());

        // Recursively delete the node from the right subtree
        node->setRight(DeleteNode(node->getRight(), temp->getTime()));
    }
    return node;
}

// Find the minimum node in the right subtree
SubtitleBSTNode* SubtitleBST::FindMin(SubtitleBSTNode* node) {
    while (node->getLeft() != nullptr) {
        node = node->getLeft();
    }
    return node;
}

// Delete all nodes with times earlier than the target time
bool SubtitleBST::DeleteNodesUnder(string targetTime) {
    bool found = false;
    root = DeleteNodesUnderHelper(root, targetTime, found);
    return found;
}

// Recursive helper function to delete nodes with times earlier than the target time
SubtitleBSTNode* SubtitleBST::DeleteNodesUnderHelper(SubtitleBSTNode* node, string targetTime, bool& found) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->getTime() < targetTime) {
        found = true;
        SubtitleBSTNode* rightSubtree = node->getRight();
        delete node;
        return DeleteNodesUnderHelper(rightSubtree, targetTime, found);
    }

    node->setLeft(DeleteNodesUnderHelper(node->getLeft(), targetTime, found));
    return node;
}