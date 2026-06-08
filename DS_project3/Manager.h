#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "GraphMethod.h"

class Manager{ // manager class
private:
	Graph* graph; // graph
	ofstream fout; // file stream
	int load; // load

public:
	Manager(); // manager constructor
	~Manager(); // manager destructor

    // program run fuction
	void run(const char * command_txt);
	
    // graph textfile load function
	bool LOAD(string filename);
    
    // graph print function
	bool PRINT();
	
    // BFS function
	bool mBFS(int vertex);
    
    // DFS_R function
	bool mDFS_R(int vertex);
    
    // DFS function
	bool mDFS(int vertex);
    
    // DIJKSTRA function
	bool mDIJKSTRA(int vertex);
    
    // KRUSKAL function
	bool mKRUSKAL();
    
    // BELLMANFORD function
	bool mBELLMANFORD(int s_vertex, int e_vertex);
    
    // FLOYD function
	bool mFLOYD();

    //print error code
	void printErrorCode(int n);	
};

#endif
