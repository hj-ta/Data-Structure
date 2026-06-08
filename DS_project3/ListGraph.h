#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph{  // list graph class
private:
	map < int, int >* m_List;

public:	
	ListGraph(bool type, int size); // listGraph constructor
	~ListGraph();  // listgraph destructor
		
    
    // Adjacent Vertices save fuction (no direction)
	void getAdjacentEdges(int vertex, map<int, int>* m);
    
    // Adjacent Vertices save fuction direction existing
    void getAdjacentEdges_d(int vertex, map<int, int>* m);
    
    // insert edge information in graph
	void insertEdge(int from, int to, int weight);
    
    // print graph
	bool printGraph(ofstream* fout);
    
};

#endif
