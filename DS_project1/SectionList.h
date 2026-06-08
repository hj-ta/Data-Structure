#pragma once
#include "SectionListNode.h"

class SectionList
{
private:
	SectionListNode* head;
	// Pointer to the first section node in the list

public:
	
	SectionList(); // Constructor declaration
	~SectionList(); // Destructor declaration
	

	SectionListNode* getHead();
	// Is a setter needed?

	// Function declarations
	void addSection(int sectionNumber, SubtitleListNode* contentHead);
	SectionListNode* findSection(int sectionNumber) const;

};