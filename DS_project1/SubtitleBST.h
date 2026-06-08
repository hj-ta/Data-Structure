#pragma once
#include "SubtitleBSTNode.h"
#include <string>
#include "SubtitleListNode.h"

using namespace std;

class SubtitleBST
{
private:
	SubtitleBSTNode* root; // Root node of the binary search tree

	// Recursive function to insert a node into the tree
	SubtitleBSTNode* InsertNode(SubtitleBSTNode* node, string time, string content);

	// Recursive function to perform in-order traversal and print the tree
	void InOrderPrint(SubtitleBSTNode* node, ofstream& flog);

	// Recursive function to search for a specific subtitle time
	SubtitleBSTNode* SearchNode(SubtitleBSTNode* node, string time);

	// Recursive function to delete a node from the tree
	SubtitleBSTNode* DeleteNode(SubtitleBSTNode* node, string time);

	// Function to find the minimum value in the right subtree
	SubtitleBSTNode* FindMin(SubtitleBSTNode* node);

	// Recursive function to delete all nodes in the tree
	void DestroyTree(SubtitleBSTNode* node);

	// Recursive helper function to search for nodes within a time range
	bool FindNodesInRangeHelper(SubtitleBSTNode* node, string startTime, string endTime, SubtitleListNode*& contentHead, SubtitleListNode*& lastContentNode);

	// Recursive helper function to delete nodes earlier than a specific time
	SubtitleBSTNode* DeleteNodesUnderHelper(SubtitleBSTNode* node, string targetTime, bool& found);

public:
	// Constructor
	SubtitleBST();
	
	// Destructor
	~SubtitleBST();

	// Getter to return the root node, no setter needed as the tree should manage its own structure
	SubtitleBSTNode* getRoot();

	// Insert a new node into the tree with a subtitle time and content
	void Insert(string time, string content);

	// Print the tree using in-order traversal
	void Print(ofstream& flog);

	// Search for a specific node by subtitle time
	SubtitleBSTNode* Search(string time);

	// Delete a node with a specific subtitle time
	void Delete(string time);

	// Delete all nodes with subtitle times earlier than the target time
	bool DeleteNodesUnder(string targetTime);

	// Find all nodes within a given time range and link them into a list
	bool FindNodesInRange(string startTime, string endTime, SubtitleListNode*& contentHead, SubtitleListNode*& lastContentNode);
};