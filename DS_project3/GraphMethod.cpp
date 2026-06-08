#include "GraphMethod.h"

bool BFS(Graph* graph, int vertex, ofstream* fout) // BFS function
{
    int signal = 0;
    int size = graph->getSize(); // graph size
    
    map<int,int>* m = new map<int, int>[size]; // map to save vertex and weight
    bool* visited = new bool[size]; // visited check array
    visited[vertex] = true; // start vertex visit
    
    queue<int> q; // queue
    q.push(vertex); // push start vertex
    
    if(vertex > size-1) // don'h have vertex
    {
        delete[] m;
        delete[] visited;
        
        return false;
    }
        
    vector<int> print_v; // vector for print path
    while (!q.empty())
    {
        int x = q.front(); // queue's front

        print_v.push_back(x); // push vertex
        q.pop(); // queue pop
        
        signal = 1;
        graph->getAdjacentEdges(x, m); // get adjacent edges in m
        
        for(auto it_ = m[x].begin(); it_ != m[x].end(); it_++)
        {
            if(!visited[it_->first])  // don't visit
            {
                q.push(it_->first);
                visited[it_->first] = true;
            }
        }
    }
    

    delete[] visited;
    delete[] m;
    
    *fout << "========BFS========\n";
    *fout << "startvertex : " << vertex << "\n";
    
    for(auto it = print_v.begin(); it != print_v.end(); it++) // print BFS path
    {
        
        *fout << *it;
        if((it+1) != print_v.end())
        {
            
            *fout <<" -> ";
        }
    }
    
    *fout <<"\n";
    print_v.clear(); // vector clear
    vector<int>().swap(print_v);
    return true;
}

bool DFS(Graph* graph, int vertex, ofstream* fout) // DFS function
{
    int size = graph->getSize(); // graph size
    map<int,int>* m = new map<int, int>[size]; // map to save vertex and weight
    bool* visited = new bool[size]; // visited check array
    
    if(vertex > size-1) // don'h have vertex
    {
        delete[] visited;
        delete[] m;
        
        return false;
    }
    
    vector<int> print_v; // vector to print path
    
    stack<int> s; // stack
    s.push(vertex); // push start vertex
    visited[vertex] = true; // visit start vertex
    print_v.push_back(vertex);
    cout << vertex <<  "\n";
    
    while (!s.empty()) // while stack is empty
    {
        int current = s.top(); // current vertex
        s.pop();
        
        graph->getAdjacentEdges(current, m); // get adjancent edges
        
        for(auto it_ = m[current].begin(); it_ != m[current].end(); it_++)
        {
            int next = it_->first; // next edge is adjacent vertex
            if(!visited[next]) // don't visit
            {

                print_v.push_back(next);
                visited[next] = true;
                
                s.push(current);
                s.push(next);
                break;
            }
        }
    }

    delete[] visited;
    delete[] m;
    
    *fout << "========DFS========\n";
    *fout << "startvertex : " << vertex << "\n";
    
    for(auto it = print_v.begin(); it != print_v.end(); it++) // print DFS path
    {
        *fout << *it;
        if((it+1) != print_v.end())
        {
            *fout <<" -> ";
        }
    }
    *fout <<"\n";
    print_v.clear();
    vector<int>().swap(print_v);
    
    return true;
}

bool DFS_R(Graph* graph, bool* visit, int vertex,  map<int, int>* m, ofstream* fout) // DFS_R function
{
    vector<int> print_v; // vector to print path
    int size = graph->getSize(); // graph size
    
    if(vertex > size-1) // don'h have vertex
    {
        return false;
    }
    
    if(!dfs_re(graph, visit, vertex, m, &print_v)) // run DFS recursive function
    {
        print_v.clear();
        vector<int>().swap(print_v);
        return false;
    }
    
    *fout << "========DFS_R========\n";
    *fout << "startvertex : " << vertex << "\n";
    
    for(auto it = print_v.begin(); it != print_v.end(); it++) // print dfs path
    {
        *fout << *it;
        if((it+1) != print_v.end())
        {
            *fout <<" -> ";
        }
    }
    *fout <<"\n";
    print_v.clear(); // vector clear
    vector<int>().swap(print_v);
    
    return true;
}

bool dfs_re(Graph* graph, bool* visit, int vertex,  map<int, int>* m, vector<int>* v) // dfs recursive function
{
    int start = vertex; // vertex
    
    if(visit[start]) // if already visited
    {
        return false;
    }
    visit[start] = true;
    v->push_back(start); // push vertex

    graph->getAdjacentEdges(start, m);
    
    for(auto it_ = m[start].begin(); it_ != m[start].end(); it_++)
    {
        int next = it_->first;
        if(!visit[next])
        {
            dfs_re(graph, visit, next, m, v); // recursiving function
        }
    }
    
    return true;
}
bool Kruskal(Graph* graph, ofstream* fout) // kruskal function
{
    vector<pair<int, pair<int, int>>> v; // vector to save graph's information

    int size = graph->getSize(); // graph size
    int arr_size = 0; // array size
    map<int,int>* m = new map<int, int>[size];
    
    for (int i = 0; i < size; i++) // loop for size
    {
        graph->getAdjacentEdges(i, m);
        for (auto it = m[i].begin(); it != m[i].end(); it++)
        {
            if(it->second < 0) // negative weight
            {
                return false;
            }
            v.push_back(pair<int,pair<int,int>>(it->second,{i,it->first})); // save adjacent vertex and edge
            arr_size += 1;
        }
        m->clear();
    }
    
    delete[] m;
    
    int* weight_arr = new int[arr_size+1]; // weight array
    
    int index = 1;
    weight_arr[0] = 0; // don't use index 0
    for(auto it = v.begin(); it != v.end(); it++)
    {
        weight_arr[index] = it->first; // save weight information
        index += 1;
    }
    
    
    quicksort(weight_arr, 1, arr_size); // weight sort ascending to quicksort
    
    
    int* parent = new int[size]; // parent array
    
    for(int i = 0; i < size; i++)
    {
        parent[i] = i; // save same index
    }
    
    int cost = 0;
    
    int edge_count = 0;
    
    map<int,int>* mst = new map<int,int>[size]; // mst map
    
    for(int i = 1; i < arr_size + 1; i++)
    {
        for (auto it = v.begin(); it != v.end(); it++)
        {
            if(weight_arr[i] == it->first)
            {
                int start_v = it->second.first;
                int end_v = it->second.second;
                
                
                if(Find(parent,start_v) != Find(parent, end_v)) // find parent vertex and compare
                {
                    cost += it->first; // plus cost
                    mst[start_v].insert({end_v, it->first}); // insert information in mst
                    mst[end_v].insert({start_v, it->first}); // insert information in mst
                    
                    edge_count += 1;
                    Union(parent, start_v, end_v); // union start vertex and end vertex
                }
                v.erase(it--); // erase information
            }
        }
    }
    
    
    if(edge_count != size -1) // don't make mst
    {
        cout << "no tree" << endl;
        return false;
    }
    
    *fout << "========Kruskal========\n";
    
    for(int i = 0; i < size; i++) // print kruskal information
    {
        *fout << "[" << i << "] ";
        for(auto it = mst[i].begin(); it != mst[i].end(); it++)
        {
            *fout << it->first << "(" << it->second << ") ";
        }
        *fout << endl;
    }
   
    cout << "cost : " << cost << endl;
     
    
    *fout << "cost : " << cost << endl; // print mst cost
    
    
    vector<pair<int, pair<int, int>>>().swap(v);
    delete[] weight_arr;
    delete[] parent;
    delete[] mst;
    
    return true;
    
}

int Find(int parent[], int vertex) // find functino
{
    if (parent[vertex] == vertex) // return parent vertex
    {
        return vertex;
    }
    
    return parent[vertex] = Find(parent, parent[vertex]); // return parent vertex
}


void Union(int parent[], int vertex1, int vertex2) // union function
{
    int vertex1_parent = Find(parent, vertex1); // vertex1's parent vertex
    int vertex2_parent = Find(parent, vertex2); // vertex2's parent vertex
    
    if (vertex1_parent < vertex2_parent) // vertex2's parent vertex is big
    {
        parent[vertex2_parent] = vertex1_parent;
    }
    else // vertex2's parent vertex isn't big
    {
        parent[vertex1_parent] = vertex2_parent;
    }
    return;
}

void insert(int e, int* arr, int i) // insert
{
    arr[0] = e;
    while(e < arr[i])
    {
        arr[i+1] = arr[i];
        i--;
    }
    arr[i+1] = e;
}

void insertion(int* arr, int one, int two) //insert sort
{
    for(int j = one+1; j <= two; j++)
    {
        int temp = arr[j];
        insert(temp, arr, j-1);
    }
}

void quicksort(int* arr, int low, int high) // quick sort
{
    int j = 0;
    int pivot = 0;
    if(low < high)
    {
        int last = high - low + 1;
        if(last <= 6)
        {
            insertion(arr, low, high);
        }
        else
        {
            int i = low;
            j = high + 1;
            pivot = arr[low]; // pivot
            do
            {
                do i++; while(arr[i] < pivot); // low part
                do j--; while(arr[j] > pivot); // high part
                if(i < j) swap(arr[i], arr[j]); // swap
            } while(i < j);
            swap(arr[low], arr[j]);
            
            quicksort(arr, low, j-1); // quick sort low part
            quicksort(arr, j+1, high); // quick sort high part
        }
    }
    return;
}



bool Dijkstra(Graph* graph, int vertex, ofstream* fout) // DIJKSTRA function
{
    int size = graph->getSize(); // graph size
    map<int,int>* m = new map<int, int>[size];
    
    if(vertex > size-1) // don't have vertex
    {
        return false;
    }
    
    bool* visited = new bool[size]; // visited check array
    fill(visited, visited + size, false);
    
    int* distance = new int[size]; // distance array
    int* path = new int[size]; // path array
    
    
    int** length = new int*[size]; // distance from vertex to vertex
    
    for(int i = 0; i < size; i++) // initialize and allocate length
    {
        length[i] = new int[size];
        path[i] = MAX;
    }
    
    for(int i = 0; i < size; i++) // initialize length
    {
        for(int j = 0; j < size; j++)
        {
            length[i][j] = MAX;
        }
    }
    
    for(int i = 0; i < size; i++) // loop for size
    {
        graph->getAdjacentEdges_d(i, m); // get adjancent edges
        for(auto it = m[i].begin(); it != m[i].end(); it++)
        {
            for(int j = 0; j < size; j++) // loop for size
            {
                if(it->second < 0)
                {
                    cout << "neg weight : " << it->second << endl;
                    return false;
                }
                if(j == it->first) // save weight in length
                {
                    length[i][j] = it->second;
                }
            }
        }
    }
    
    
    for(int i = 0; i < size; i++) // loop for size
    {
        visited[i] = false;
        distance[i] = length[vertex][i];
        if(length[vertex][i] != MAX) // save path
        {
            path[i] = vertex;
        }
    }
    
    
    for(int i = 0; i < size-2; i++)
    {
        graph->getAdjacentEdges_d(i, m);
        int min_d = MAX;
        int index = 0;
        for(int j = 0; j < size; j++)
        {
            if(min_d > distance[j] && visited[j] == false) // find min weight for adjacent edges
            {
                min_d = distance[j];
                index = j;
            }
        }
        int u = index; // min vertex
        cout << "index : " << index << endl;
        visited[u] = true;
        
        int prev = 0;
        
        for(int w = 0; w < size; w++) // loop for size
        {
            if(visited[w] == false)
            {
                prev = distance[w];
                distance[w] = min(distance[u] + length[u][w], distance[w]); // compare
                if(distance[w] < prev)
                {
                    if(w != vertex)
                    {
                        path[w] = u; // update path
                    }
                }
            }
        }
    }
    *fout << "========Dijkstra========\n";
    *fout << "startvertex: " << vertex << endl;
    for(int i = 0; i < size; i++) // print dijkstra information
    {
        vector<int> p;
        int id = 0;
        id = i;
        if(i == vertex)
        {
            continue;
        }
        *fout << "[" << i << "] ";
        if(path[id] == MAX)
        {
            *fout << "x\n";
            continue;
        }
        
        while(id != MAX)
        {
            
            p.push_back(id);
            id = path[id];
        }
        
        reverse(p.begin(), p.end());
        
        for(auto it = p.begin(); it != p.end(); it++)
        {
            *fout << *it;
            if((it+1) != p.end())
            {
                *fout <<" -> ";
            }
        }
        *fout << " (" << distance[i] << ")" << "\n";
        
        p.clear();
        
    }
    
    for(int i = 0; i < size; i++)
    {
        delete[] length[i];
        
    }
    delete[] length;
    
    delete[] m;
    delete[] visited;
    
    delete[] path;
    delete[] distance;
    
    
    
    return true;
}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex, ofstream* fout) // Bellmanford function
{
    int size = graph->getSize(); // graph size
    map<int,int>* m = new map<int, int>[size];
    
    if((s_vertex > size) or (e_vertex > size)) // don't have vertex
    {
        return false;
    }
    
    int* distance = new int[size]; // distance array
    int* path = new int[size]; // path array
    
    
    int** length = new int*[size]; // length array
    
    for(int i = 0; i < size; i++) // initialize path and allocate length
    {
        length[i] = new int[size];
        path[i] = MAX;
    }
    
    for(int i = 0; i < size; i++) // initialize length
    {
        for(int j = 0; j < size; j++)
        {
            length[i][j] = MAX;
        }
    }
    
    for(int i = 0; i < size; i++) // save edge's information in length
    {
        graph->getAdjacentEdges_d(i, m);
        for(auto it = m[i].begin(); it != m[i].end(); it++)
        {
            for(int j = 0; j < size; j++)
            {
                if(j == it->first)
                {
                    length[i][j] = it->second;
                }
            }
        }
    }
    
    for(int i = 0; i < size; i++) // save distance and path
    {
        distance[i] = length[s_vertex][i];
        if(length[s_vertex][i] != MAX)
        {
            path[i] = s_vertex;
        }
    }
        
    distance[s_vertex] = 0;
    
    for(int k = 2; k < size - 1; k++)
    {
        for (int v = 0; v < size; v++) // loop for size
        {
            if (v != s_vertex)
            {
                int prev = 0;
                
                for(int w = 0; w < size; w++) // loop for size
                {
                    if(length[w][v] != MAX)
                    {
                        prev = distance[v];
                        if(distance[w] == MAX || length[w][v] == MAX) // erroe case
                        {
                            continue;
                        }
                        distance[v] = min(distance[v], distance[w] + length[w][v]); // compare distance
                        if(distance[v] < prev)
                        {
                            path[v] = w;
                        }
                    }
                }
            }
        }
    }
    
    for (int v = 0; v < size; v++) // check negatice cycle
    {
        if (v != s_vertex)
        {
            int prev = 0;
            
            for(int w = 0; w < size; w++) // loop for size
            {
                if(length[w][v] != MAX)
                {
                    prev = distance[v];
                    if(distance[w] == MAX || length[w][v] == MAX)
                    {
                        continue;
                    }
                    distance[v] = min(distance[v], distance[w] + length[w][v]);
                    if(distance[v] < prev)
                    {
                        cout << "error error\n";
                        return false;
                    }
                }
            }
        }
    }
    
    int id = e_vertex;
    
    vector<int> p;

    while(id != MAX)
    {
        p.push_back(id);
        id = path[id];
    }

    reverse(p.begin(), p.end());

    *fout << "========Bellman-Ford========\n";     // print Bellman ford
    if(distance[e_vertex] == MAX)
    {
        *fout << "x \n";
    }
    else
    {
        for(auto it = p.begin(); it != p.end(); it++)
        {
            *fout << *it;
            if((it+1) != p.end())
            {
                *fout <<" -> ";
            }
        }
        *fout << " (" << distance[e_vertex] << ")" << "\n";
    }
    
    p.clear();

    for(int i = 0; i < size; i++)
    {
        delete[] length[i];
        
    }
    delete[] length;
    
    delete[] m;
    
    delete[] path;
    delete[] distance;
    vector<int>().swap(p);
    
    return true;
}

bool FLOYD(Graph* graph, ofstream* fout) // floyd function
{
    int size = graph->getSize(); // graph size
    int** length = new int*[size]; // length array
    
    map<int,int>* m = new map<int, int>[size]; //
    
    for(int i = 0; i < size; i++) // allocate length
    {
        length[i] = new int[size];
    }
    
    for(int i = 0; i < size; i++) // loop for size
    {
       
        for(int j = 0; j < size; j++) // length initialize
        {
            if(j == i)
            {
                length[i][j] = 0;
                cout << "i : " << i << "j : " << j << "len : " << length[i][j] << endl;
            }
            else
            {
                length[i][j] = MAX;
            }
            
        }
    }
    
    for(int i = 0; i < size; i++) // save edge in length
    {
        graph->getAdjacentEdges_d(i, m);
        for(auto it = m[i].begin(); it != m[i].end(); it++)
        {
            for(int j = 0; j < size; j++)
            {
                if(j == it->first)
                {
                    length[i][j] = it->second;
                }
            }
        }
    }
    
    // floyd alforithm
    for(int k = 0; k < size; k++) // via vertex
    {
        for(int i = 0; i < size; i++) // start vertex
        {
            for(int j = 0; j < size; j++) // end vertex
            {
                if(length[i][k] == MAX || length[k][j] == MAX)
                {
                    continue;
                }
                length[i][j] = min(length[i][j], length[i][k] + length[k][j]); // compare distance
                
                
            }
        }
    }
    
    for(int k = 0; k < size; k++) // check negative cycle
    {
        for(int i = 0; i < size; i++)
        {
            int prev = 0;
            for(int j = 0; j < size; j++)
            {
                prev = length[i][j];
                if(length[i][k] == MAX || length[k][j] == MAX)
                {
                    continue;
                }
                length[i][j] = min(length[i][j], length[i][k] + length[k][j]);
                if(length[i][j] < prev)
                {
                    cout << "error error\n";
                    return false;
                }
            }
        }
    }
    
    *fout << "========Floyd========\n"; // print all vertex and min distance
    
    *fout<<'\t';
    for(int i = 0; i < size; i++)
    {
        *fout<<"["<<i<<"]"<<'\t';
    }
    *fout<<endl;

    for(int i=0; i < size; i++)
    {
        *fout<<"[" << i << "]";
        for(int j = 0; j < size && *fout<<'\t'; j++)
        {
            if(length[i][j] == MAX)
            {
                *fout << "x";
            }
            else
            {
                *fout << length[i][j];
            }
        }
        *fout << endl;
    }
    
    *fout << "==============================\n\n";
    for(int i = 0; i < size; i++)
    {
        delete[] length[i];
        
    }
    delete[] length;
      
    delete[] m;
    
    return true;
}
