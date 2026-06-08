#pragma once
#include <string>
using namespace std;

class SubtitleQueueNode {
private:
    string time;      // Time of the subtitle
    string content;   // Content of the subtitle
    SubtitleQueueNode* next;  // Pointer to the next node

public:
    // Getter for the subtitle time
    string getTime() { return time; }

    // Getter for the subtitle content
    string getContent() { return content; }

    // Getter for the next node pointer
    SubtitleQueueNode* getNext(){ return next; }

    // Setter for the subtitle time
    void setTime(string time) { this->time = time; }

    // Setter for the subtitle content
    void setContent(string content) { this->content = content; }

    // Setter for the next node pointer
    void setNext(SubtitleQueueNode* next) { this->next = next; }

    // Constructor: Initializes subtitle time and content
    SubtitleQueueNode(string time, string content) {
        this->time = time;
        this->content = content;
        next = nullptr;
    }
	
    // Destructor
    ~SubtitleQueueNode() {}
};