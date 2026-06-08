#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size) // matrixgraph constructor
{
	m_Mat = new int*[size];
	for(int i=0; i<size; i++)
	{
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int)*size);
	}
}

MatrixGraph::~MatrixGraph() // matrixgraph destructor
{
    cout << "delete M\n";
	for(int i=0; i<getSize(); i++)
	{
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
}

// Adjacent Vertices save fuction (no direction)
void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
    int weight = 0; // weight
    for(int i = 0; i < m_Size; i++)
    {
        for(int j = 0; j < m_Size; j++)
        {
            weight = m_Mat[i][j];
            if(i == vertex)
            {
                if(m_Mat[i][j] != 0)
                {
                    if(m_Mat[j][i] != 0)
                    {
                        if(weight < m_Mat[j][i])
                        {
                            m[i].insert({j, weight});    // i = start vertex, j = end vertex
                        }
                    }
                    else
                    {
                        m[i].insert({j, weight});    // i = start vertex, j = end vertex
                    }
                }
            }
            else
            {
                if(j == vertex)
                {
                    if(m_Mat[i][j] != 0)
                    {
                        if(m_Mat[j][i] != 0)
                        {
                            if(weight < m_Mat[i][j])
                            {
                                m[j].insert({i, weight});    // j = start vertex, i = end vertex
                            }
                        }
                        else
                        {
                            m[j].insert({i, weight});    // j = start vertex, i = end vertex
                        }
                    }
                }
            }
        }
    }
}

// Adjacent Vertices save fuction direction existing
void MatrixGraph::getAdjacentEdges_d(int vertex, map<int, int>* m)
{
    int weight = 0; // weight
    for(int i = 0; i < m_Size; i++)
    {
        for(int j = 0; j < m_Size; j++)
        {
            weight = m_Mat[i][j];
            if(m_Mat[i][j] != 0) // if connected vertex
            {
                m[i].insert({j, weight});
            }
        }
    }
}

void MatrixGraph::insertEdge(int from, int to, int weight) // insert edge information in graph
{
    m_Mat[from][to] = weight;
}


bool MatrixGraph::printGraph(ofstream* fout) // print graph
{
	if( m_Size < 0 )
		return 0;

    *fout << "========PRINT========\n";
    *fout<<'\t';
	for(int i=0; i<m_Size; i++)    // loop for m_size
	{
        *fout<<"["<<i<<"]"<<'\t';
	}
	*fout<<endl;

	for(int i=0; i<m_Size; i++) // loop for m_size
	{
		
        *fout<<"["<<i<<"]";
		for(int j=0; j<m_Size && *fout<<'\t'; j++) // loop for m_size
		{
			*fout<<m_Mat[i][j]; // print weight
		}
		*fout<<endl;
	}
	return 1;
}
