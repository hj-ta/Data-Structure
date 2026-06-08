#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size) // listGraph constructor
{
	m_Type = type;
	m_List = new map<int, int>[size];
}

ListGraph::~ListGraph() // listgraph destructor
{
    cout << "delete L\n";
	delete[] m_List;
}

// Adjacent Vertices save fuction (no direction)
void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
    for(int i = 0; i < m_Size; i++)
    {
        for(auto it_ = m_List[i].begin(); it_ != m_List[i].end(); it_++)
        {
            if(i == vertex)
            {
                auto iter = m_List[it_->first].find(i); // if end vertex's weight exist
                if(iter != m_List[it_->first].end())
                {
                    if(it_->second < iter->second)
                    {
                        m[vertex].insert({it_->first, it_->second});
                    }
                }
                else // no end vertex's weight
                {
                    m[vertex].insert({it_->first, it_->second});
                }
            }
            else
            {
                if(it_->first == vertex)
                {
                    auto iter = m_List[it_->first].find(i);
                    if(iter != m_List[it_->first].end()) // if end vertex's weight exist
                    {
                        if(it_->second < iter->second)
                        {
                            m[vertex].insert({i, it_->second});
                        }
                    }
                    else // no end vertex's weight
                    {
                        m[vertex].insert({i, it_->second});
                    }
                }
            }
        }
    }
}

// Adjacent Vertices save fuction direction existing
void ListGraph::getAdjacentEdges_d(int vertex, map<int, int>* m)
{
    for(int i = 0; i < m_Size; i++)
    {
        for(auto it_ = m_List[i].begin(); it_ != m_List[i].end(); it_++)
        {
            if(i == vertex)
            {
                m[vertex].insert({it_->first, it_->second}); // insert weight and vertex information
            }
        }
    }
}


// insert edge information in graph
void ListGraph::insertEdge(int from, int to, int weight)
{
    m_List[from].insert({to, weight});
}

// print graph
bool ListGraph::printGraph(ofstream* fout)
{
    if( m_Size < 0 )
        return 0;
    *fout << "========PRINT========\n";
	for(int i=0; i<m_Size; i++)  // loop for m_size
	{
		
        *fout << "[" << i << "]";

		for(auto it_=m_List[i].begin(); it_!=m_List[i].end() && *fout <<" -> "; it_++)  // loop for m_size
		{
			
            *fout<<"("<<it_->first<<","<<it_->second<<")"; // print vertex and weight
		}
		*fout<<endl;
	}
	*fout<<endl;
	return 1;
}


