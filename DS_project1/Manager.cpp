#include <sstream>
#include "Manager.h"

using namespace std;

//Constructor_queue, BST, and section list
Manager::Manager(){
    ManagerQueue = new SubtitleQueue();
    subtitleBST = new SubtitleBST();
    sectionList = new SectionList();
}

// Destructor
Manager::~Manager(){
    delete ManagerQueue;
    delete subtitleBST;
    delete sectionList;
}
//Run Function
void Manager::Run(const char* command)
{
    // Open command and log file
    fcmd.open(command);
    flog.open("log.txt");

    // Check if the command file opens successfully
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1); //if not, exit 
    }

    //Buffer to store each line from the command file
    string cmdBuffer;

    // Read commands line by line
    while (getline(fcmd, cmdBuffer)) {
        istringstream iss(cmdBuffer);
        string cmd;
        vector<string> v;

        // Split the command into individual parts and store in vector
        while (iss >> cmd) {
            v.push_back(cmd);
        }

        // Execute the appropriate function based on the command
        // LOAD command
        if (v[0] == "LOAD") {
            if(v.size() == 1) LoadSubtitle(); //check argument number
            else PrintErrorCode(100); // Error if arguments are incorrect
        }
        // QPOP command
        else if (v[0] == "QPOP") {
            if(v.size() == 1) QPOP(); //check argument number
            else PrintErrorCode(200); // Error if arguments are incorrect
        }
        // PRINT command
        else if (v[0] == "PRINT") {
           Print(v);
        }
        //SECTION command
        else if (v[0] == "SECTION") {
           Section(v);
        }
        //DELETE command
        else if(v[0]=="DELETE"){
            // DELETE EQUAL command
            if(v[1]=="EQUAL" && v.size() == 3){ //check argument number
                // Find the node
                SubtitleBSTNode* node = subtitleBST->Search(v[2]);
                if(node != nullptr){
                    
                    subtitleBST->Delete(v[2]); // Delete the found node
                    PrintSuccess("DELETE");
                }
                else{
                    PrintErrorCode(500); // Error if the node is not found
                }
            }
            // DELETE UNDER command
            else if(v[1] == "UNDER" && v.size() == 3){
                bool found = subtitleBST->DeleteNodesUnder(v[2]);
                if(found){
                    PrintSuccess("DELETE");
                }
                else{
                    PrintErrorCode(500); // Error if no nodes found to delete
                }
            }
            else{
                PrintErrorCode(500); //for check argument number
            }
        }
        //EXIT command
        else if(v[0] == "EXIT"){
            if(v.size() == 1) ExitProgram(); //for check argument number
            else PrintErrorCode(1000);
        }
        else{
            PrintErrorCode(1000); // Error for invalid command
        }
    }

    // Close files at the end of execution
    fcmd.close();
    flog.close();
    return;
}

// Function to print a success message
void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============\n" << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============\n" << endl;
}

///////////////LOAD//////////////////////
// LOAD command _ loads subtitles from a file into the queue
void Manager::LoadSubtitle() {
    ifstream fdata("subtitle.txt"); // Open subtitle data file

     // If the file cannot be opened, print an error
    if (!fdata.is_open()) {
        PrintErrorCode(100); 
        return;
    }
    string line;  // Buffer to store each line from the file
    // Read the file line by line
    while (getline(fdata, line)) {
        istringstream iss(line);
        string time;
        string content;
        
        // Extract the time and content from each line
        iss >> time; // Read the time
        getline(iss, content); // Read the content

        // Remove leading space from content
        if (!content.empty() && content[0] == ' ') {
            content.erase(0, 1);
        }
        // Push time and content to the queue
        ManagerQueue->Push(time, content);
    }

    fdata.close(); //Close the subtitle file

   // Print the contents of the queue to the log
    PrintQueueContents();
}

// Function to print the queue contents to the log
void Manager::PrintQueueContents() {
    SubtitleQueueNode* current = ManagerQueue->Front(); // Get the front of the queue
    flog << "===== LOAD =====" << endl;

    // Loop through the queue and print each node
    while (current != nullptr) {
        flog << current->getTime() << " - " << current->getContent() << endl;
        current = current->getNext(); // Move to the next node
    }

    flog << "===============\n" << endl;
}

////////////////// QPOP////////////////////
// QPOP Function_ Pop all subtitles from the queue and insert them into the BST
void Manager::QPOP(){
    if(ManagerQueue->IsEmpty()){
        PrintErrorCode(200);
        return;
    }
    
    while (!ManagerQueue->IsEmpty()) {
        SubtitleQueueNode* current = ManagerQueue->Front();  // Fetch the front node again
        subtitleBST->Insert(current->getTime(), current->getContent()); // Insert into the BST
        ManagerQueue->Pop(); // Pop and delete the node
    }

    PrintSuccess("QPOP");
}


///////////////////PRINT///////////////////
// PRINT Function _ Print the BST or a section
void Manager::Print(const vector<string>& v) {
    // If only PRINT is given (no extra)
    if (v.size() == 1) { 
        if (subtitleBST->getRoot() == nullptr) {
            PrintErrorCode(300); // Error if the BST is empty
            return;
        }
        // Print the BST
        flog << "===== PRINT =====" << endl;
        flog << "Subtitle_BST" << endl;
        subtitleBST->Print(flog); 
        flog << "===============\n" << endl;
    }

    // If PRINT <section_number> is given
    else if (v.size() == 2) { 
        int sectionNumber = stoi(v[1]);
        SectionListNode* section = sectionList->findSection(sectionNumber);
        if (section == nullptr) {
            PrintErrorCode(300); // Error if the section is not found
            return;
        }
        // Print
        flog << "===== PRINT =====" << endl;
        flog << "Section " << sectionNumber << endl;
        SubtitleListNode* content = section->getContentHead();
        while (content != nullptr) {
            flog << content->getTime() << " - " << content->getContent() << endl;
            content = content->getNext();
        }
        flog << "===============\n" << endl;
    }
}

////////////// SECTION///////////
// SECTION function _ Finds and adds a section to the section list
void Manager::Section(const vector<string>& v) {
   // Ensure the command has exactly four parts (SECTION number start_time end_time)
    if (v.size() != 4) {  
        PrintErrorCode(400); // Error if arguments are incorrect
        return;
    }

    int sectionNumber = stoi(v[1]); // Convert section number to integer
    string startTime = v[2]; // Get start time
    string endTime = v[3]; // Get end time

    // Search for nodes within the time range and link them
    SubtitleListNode* contentHead = nullptr;
    SubtitleListNode* lastContentNode = nullptr;

    // Search for nodes within the time range and link them  
    bool foundNodes = subtitleBST->FindNodesInRange(startTime, endTime, contentHead, lastContentNode);

    // If no nodes are found, return an error
    if (!foundNodes) {  
        PrintErrorCode(400);
        return;
    }

    // Add the section to the section list
    sectionList->addSection(sectionNumber, contentHead);

    // Print success message
    PrintSuccess("SECTION");
}

//////////////DELETE////////////
///// DELETE Function_ Deletes a node from the BST
void Manager::Delete(const vector<string>& v) {
    // Ensure the command has enough arguments
    if (v.size() < 3) {
        PrintErrorCode(500); // Error if arguments are incorrect
        return;
    }

    string option = v[1]; // EQUAL or UNDER
    string targetTime = v[2]; // Target time for deletion

    // Check if the BST is empty
    if (subtitleBST->getRoot() == nullptr) {
        PrintErrorCode(500); // Error if BST is empty
        return;
    }

    // DELETE EQUAL _ deletes a node with the exact time
    if (option == "EQUAL") {
        SubtitleBSTNode* targetNode = subtitleBST->Search(targetTime);
        if (targetNode == nullptr) {
            PrintErrorCode(500); // Error if no node is found
            return;
        }
        subtitleBST->Delete(targetTime);
        PrintSuccess("DELETE");
    }
     // DELETE UNDER _ deletes nodes with times earlier than the given time
    else if (option == "UNDER") { 
    bool found = subtitleBST->DeleteNodesUnder(targetTime);
       
        if (!found) {
           PrintErrorCode(500); // Error if no nodes are found
           return;
        }
        PrintSuccess("DELETE"); 
    }
    else {
        PrintErrorCode(500); // Error for incorrect DELETE command
    }
}

//////////////EXIT///////////
// EXIT command: Frees memory and exits the program
void Manager::ExitProgram() {
  
    // Free allocated memory
    delete ManagerQueue;
    delete subtitleBST;
    delete sectionList;

    // Print success message for EXIT
    flog << "===== EXIT =====" << endl;
    flog << "Success" << endl;
    flog << "===============\n" << endl;

    // Close files and exit the program
    fcmd.close();
    flog.close();
    exit(0);
}