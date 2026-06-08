#pragma once
#include "SubtitleListNode.h"

class SectionListNode
{
private:
	int sectionNumber; // Section number
	SubtitleListNode* contentHead; // Pointer to the first subtitle node (content)
	SectionListNode* next; // Pointer to the next section node

public:
	// Constructor initializing section number and setting pointers to nullptr
	SectionListNode(int sectionNumber)
		: sectionNumber(sectionNumber), contentHead(nullptr), next(nullptr) {}

	// Destructor (not required here as no dynamic memory allocation is involved)
	~SectionListNode() {}

	// Getter functions for sectionNumber, contentHead, and next pointer
	int getSectionNumber() const { return sectionNumber; }
	SubtitleListNode* getContentHead() const { return contentHead; }
	SectionListNode* getNext() const { return next; }

	// Setter for contentHead, assigns the pointer to the head of the content list
	void setContentHead(SubtitleListNode* head) { this->contentHead = head; }

	// Setter for next, assigns the pointer to the next section node
	void setNext(SectionListNode* next)	{ this->next = next; }
};
