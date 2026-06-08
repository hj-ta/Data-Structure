#pragma once

#include <string>

using namespace std;

class SubtitleBSTNode
{
private:
	// Variables to store the subtitle time and content
	string time;
	string content;
	
	// Pointers to the left and right child nodes in the binary search tree
	SubtitleBSTNode* left;
	SubtitleBSTNode* right;

public:
    // Constructor to initialize the time, content, and set left and right pointers to nullptr
	SubtitleBSTNode(string time, string content)
        : time(time), content(content), left(nullptr), right(nullptr) {}

	// Destructor (no dynamic memory to clean up in this class, so it's empty)
	~SubtitleBSTNode() {}

	// Getter for the left child node pointer
	SubtitleBSTNode* getLeft() { return left; }

	// Getter for the right child node pointer
	SubtitleBSTNode* getRight() { return right; }

	// Setter for the left child node pointer
	void setLeft(SubtitleBSTNode* left) { this->left = left; }

	// Setter for the right child node pointer
	void setRight(SubtitleBSTNode* right) { this->right = right; }

	// Getter for the subtitle time
	string getTime() { return time; }

	// Getter for the subtitle content
	string getContent() { return content; }

	// Setter for the subtitle time
	void setTime(string time) { this->time = time; }

	// Setter for the subtitle content
	void setContent(string content) { this->content = content; }
};