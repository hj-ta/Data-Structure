#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Graph.h"

class MatrixGraph : public Graph{  // matrix graph class
private:
	int** m_Mat;

public:
	MatrixGraph(bool type, int size); // matrixGraph constructor
	~MatrixGraph();	// matrixgraph destructor
		
    // Adjacent Vertices save fuction direction existing
    void getAdjacentEdges_d(int vertex, map<int, int>* m);
    // Adjacent Vertices save fuction (no direction)
	void getAdjacentEdges(int vertex, map<int, int>* m);
    
    // insert edge information in graph
	void insertEdge(int from, int to, int weight);
    
    // print graph
	bool printGraph(ofstream* fout);
    

};

#endif
