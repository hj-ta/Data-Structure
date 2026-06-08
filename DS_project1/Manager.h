#pragma once
#include "SubtitleQueue.h"
#include "SubtitleBST.h"
#include "SectionList.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Manager {
private:
    // Input and output file streams for command file and log file
	ifstream fcmd;
	ofstream flog;
	
	// Pointers to the main components: Queue, BST, and Section List
	SubtitleQueue* ManagerQueue;
	SubtitleBST* subtitleBST;
	SectionList* sectionList;

public:
	// Constructor and Destructor to initialize and clean up memory
	Manager();
	~Manager();

	// Function to run and process commands from the input file
	void Run(const char* command);

	// Utility functions to log success or error messages to the log file
	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	// Function to load subtitle data from a file into the queue
	void LoadSubtitle();
	
	// Function to print the contents of the subtitle queue
	void PrintQueueContents();

	// Function to pop all subtitles from the queue and insert them into the BST
	void QPOP();

	// Function to print either the entire BST or a specific section
	void Print(const vector<string>& v);

	// Function to find and add a section of subtitles based on time range
	void Section(const vector<string>& v);
	
	// Function to delete a subtitle based on exact time or delete all subtitles before a specific time
	void Delete(const vector<string>& v);

	// Function to clean up resources and exit the program
	void ExitProgram();
};