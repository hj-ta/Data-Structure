#include "SubtitleQueue.h"
#include <iostream>

// Constructor: Initializes the queue
SubtitleQueue::SubtitleQueue() {
    MAX_SIZE = 100;
    front = nullptr;
    rear = nullptr;
    size = 0;
}

// Destructor: Frees dynamically allocated memory
SubtitleQueue::~SubtitleQueue() {
    while (!IsEmpty()) {
        Pop();  // Deletes all nodes until the queue is empty
    }
}

// Checks if the queue is empty
bool SubtitleQueue::IsEmpty() {
    return size == 0;
}

// Checks if the queue is full
bool SubtitleQueue::IsFull() {
    return size == MAX_SIZE;
}

// Push function: Inserts a new node into the queue
void SubtitleQueue::Push(string time, string content) {
    if (IsFull()) {
        exit(EXIT_FAILURE);  // Terminates the program if the queue is full
    }

    SubtitleQueueNode* newNode = new SubtitleQueueNode(time, content);  // Creates a new node

    if (IsEmpty()) {
        front = newNode;  // If the queue is empty, both front and rear point to the new node
        rear = newNode;
    }
    else {
        rear->setNext(newNode);  // Links the new node to the current rear node
        rear = rear->getNext();  // Moves rear to point to the new node
    }

    size++;
    return;
}

// Pop function: Removes the node at the front of the queue and deletes it
void SubtitleQueue::Pop() {
    if (IsEmpty()) {
        exit(EXIT_FAILURE);  // Terminates the program if the queue is empty
    }

    SubtitleQueueNode* temp = front;  // Temporarily stores the front node
    front = front->getNext();  // Moves front to the next node

    // If the queue becomes empty after the pop, set rear to nullptr
    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;  // Deletes the removed node
    size--;
}

////return
// Returns the node at the front of the queue without removing it
SubtitleQueueNode* SubtitleQueue::Front() {
    if (IsEmpty()) {
        exit(EXIT_FAILURE);  // Terminates the program if the queue is empty
    }

    return front;  // Returns the front node
}