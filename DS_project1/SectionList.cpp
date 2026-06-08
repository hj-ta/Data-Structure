#include "SectionList.h"

// Constructor: Initializes the head of the SectionList to nullptr
SectionList::SectionList(): head(nullptr) {
	// Do we need to add anything here?
}

// Destructor: Frees all memory associated with the SectionList
SectionList::~SectionList() {
    // Free all SectionListNodes and their associated SubtitleListNodes
    SectionListNode* current = head;
    while (current != nullptr) {
        SectionListNode* nextNode = current->getNext();

        // Free all SubtitleListNodes associated with the section
        SubtitleListNode* contentNode = current->getContentHead();
        while (contentNode != nullptr) {
            SubtitleListNode* nextContent = contentNode->getNext();
            delete contentNode; // Free the memory of the subtitle node
            contentNode = nextContent;
        }

        delete current; // Free the memory of the section node
        current = nextNode;
    }
}

// Getter for the head of the SectionList
SectionListNode* SectionList::getHead() { return head; }

/////////////// Insert Section ///////////
// Adds a new section to the SectionList
void SectionList::addSection(int sectionNumber, SubtitleListNode* contentHead) {
	SectionListNode* newSection = new SectionListNode(sectionNumber);
	newSection->setContentHead(contentHead);

	// If the list is empty, set the new section as the head
	if (head == nullptr) {
		head = newSection;
	}
	else {
		// Otherwise, find the end of the list and add the new section there
		SectionListNode* temp = head;
		while (temp->getNext() != nullptr) {
			temp = temp->getNext();
		}
		temp->setNext(newSection);
	}
}

////////// Search Section ///////////
// Searches for a section by its section number
SectionListNode* SectionList::findSection(int sectionNumber) const {
	SectionListNode* temp = head;
	while (temp != nullptr) {
		// Return the section if the section number matches
		if (temp->getSectionNumber() == sectionNumber) {
			return temp;
		}
		temp = temp->getNext();
	}
	return nullptr;  // Return nullptr if the section number is not found
}
