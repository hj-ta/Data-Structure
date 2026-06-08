#pragma once
#include "SubtitleQueueNode.h"
#include <iostream>

using namespace std;

class SubtitleQueue
{
private:
    int MAX_SIZE;                    // Maximum size of the queue
    SubtitleQueueNode* front;         // Pointer to the front of the queue
    SubtitleQueueNode* rear;          // Pointer to the rear of the queue
    int size;                         // Current size of the queue

public:
    SubtitleQueue();                  // Constructor
    ~SubtitleQueue();                 // Destructor

    bool IsEmpty();                   // Check if the queue is empty
    bool IsFull();                    // Check if the queue is full
    void Push(string time, string content); // Add a new node to the queue
    void Pop();                       // Remove a node from the front of the queue
    SubtitleQueueNode* Front();        // Return the front node without removing it
};