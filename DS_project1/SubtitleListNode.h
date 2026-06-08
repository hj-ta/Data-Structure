#pragma once
#include <string>

using namespace std;

class SubtitleListNode
{
private:
	// Variables to store the subtitle time and content
	string time;  
	string content;
	
	// Pointer to the next node in the linked list
	SubtitleListNode* next; 

public:
	// Constructor to initialize the time, content, and set the next pointer to nullptr
	SubtitleListNode(string time, string content)
		: time(time), content(content), next(nullptr) {}

	// Destructor (no dynamic memory to manage, so it's left empty)
	~SubtitleListNode() {}

	// Getter function to retrieve the subtitle time
	string getTime() const { return time; }

	// Getter function to retrieve the subtitle content
	string getContent() const { return content; }

	// Getter function to retrieve the pointer to the next node
	SubtitleListNode* getNext() { return next; }

	// Setter function to set the subtitle time
	void setTime(string time) { this->time = time; }

	// Setter function to set the subtitle content
	void setContent(string content) { this->content = content; }

	// Setter function to set the pointer to the next node
	void setNext(SubtitleListNode* next) { this->next = next; }
};
