#include "Manager.h"

Manager::Manager()  // manager constructor
{
	graph = nullptr;
	fout.open("log.txt", ios::app); // file open
	load = 0;
}

Manager::~Manager() // manager destructor
{
	if(load)
		delete graph; // delete graph
	fout.close();
}

void Manager::run(const char* command_txt) // program running
{
    ifstream fin;
    fin.open(command_txt); // command text file open

    string line;
    string word;
    
    if(!fin) // file open error
    {
        fout<< "[ERROR] command file open error!" <<endl;
        return;
    }
    
    while (!fin.eof())
    {
        getline(fin, line);
        
        if(!line.compare(""))       // ignore file end buffer
            break;
        
        if(line == "EXIT") // if line is "EXIT"
        {
            break;
        }
        else if(line == "PRINT")    //  if line is "PRINT"
        {
            if(load == 1) // if graph exist
            {
                if(PRINT() == false) // PRINT ERROR
                {
                    printErrorCode(200);
                }
                else
                {
                    fout << "==============================\n\n";
                }
            }
            else
            {
                printErrorCode(200);
            }
            
        }
        else if(line == "KRUSKAL")    //  if line is "KRUSKAL"
        {
            if(load == 1) // if graph exist
            {
                if(mKRUSKAL() == false) // KRUSKAL ERROR
                {
                    printErrorCode(600);
                }
                else
                {
                    fout << "==============================\n\n";
                }
            }
            else
            {
                printErrorCode(600);
            }
        }
        else if(line == "FLOYD")    //  if line is "FLOYD"
        {
            if(load == 1) // if graph exist
            {
                if(mFLOYD() == false) // FLOYD ERROR
                {
                    printErrorCode(900);
                }
                else
                {
                    fout << "==============================\n\n";
                }
            }
            else
            {
                printErrorCode(900);
            }
            
        }
        else
        {
            char* ptr;
            char str_p[1000] = {0,};
            string path;
            strcpy(str_p,line.c_str());
            ptr = strtok(str_p, " ");
            std::string str(ptr);
            word = ptr;
            
            if(word == "LOAD") // if word is "LOAD"
            {
                ptr = strtok(NULL, "\n");
                
                if(ptr == NULL) // no filename
                {
                    printErrorCode(100);
                    continue;
                }
                
                path = ptr;        // input file directory
                

                path.erase(std::remove_if(path.begin(), path.end(), ::isspace), path.end());

                if(LOAD(path) == false) // LOAD ERROR
                {
                    printErrorCode(100);
                }
                else
                {
                    load = 1;
                    fout << "==============================\n\n";
                }
            }
            else if(word == "BFS")  //  if word is "BFS"
            {
                ptr = strtok(NULL, "\n");
                 
                if(ptr == NULL) // no vertex
                {
                    printErrorCode(300);
                    continue;
                }
                
                path = ptr;        // input file directory

                path.erase(std::remove_if(path.begin(), path.end(), ::isspace), path.end());

                int vertex = stoi(path);
                if(load == 1) // if graph exist
                {
                    if(mBFS(vertex) == false) // BFS ERROR
                    {
                        
                        printErrorCode(300);
                    }
                    else
                    {
                        fout << "==============================\n\n";
                    }
                }
                else
                {
                    printErrorCode(300);
                }
                
            }
            else if(word == "DFS")   //  if word is "DFS"
            {
                ptr = strtok(NULL, "\n");
                
                if(ptr == NULL) // no vertex
                {
                    printErrorCode(400);
                    continue;
                }
                
                path = ptr;        // input file directory

                path.erase(std::remove_if(path.begin(), path.end(), ::isspace), path.end());

                int vertex = stoi(path);
                if(load == 1) // if graph exist
                {
                    if(mDFS(vertex) == false) // DFS ERROR
                    {
                        
                        printErrorCode(400);
                    }
                    else
                    {
                        fout << "==============================\n\n";
                    }
                }
                else
                {
                    printErrorCode(400);
                }
                
            }
            else if(word == "DFS_R")   //  if word is "DFS_R"
            {
                ptr = strtok(NULL, "\n");
                
                if(ptr == NULL) // no vertex
                {
                    printErrorCode(500);
                    continue;
                }
                
                path = ptr;        // input file directory

                path.erase(std::remove_if(path.begin(), path.end(), ::isspace), path.end());

                int vertex = stoi(path);
                
                if(load == 1) // if graph exist
                {
                    if(mDFS_R(vertex) == false) // DFS_R ERROR
                    {
                        
                        printErrorCode(500);
                    }
                    else
                    {
                        fout << "==============================\n\n";
                    }
                }
                else
                {
                    printErrorCode(500);
                }
                    
            }
            else if(word == "DIJKSTRA")  //  if word is "DIJKSTRA"
            {
                ptr = strtok(NULL, "\n");
                
                if(ptr == NULL) // no vertex
                {
                    printErrorCode(700);
                    continue;
                }
                
                path = ptr;        // input file directory

                path.erase(std::remove_if(path.begin(), path.end(), ::isspace), path.end());

                int vertex = stoi(path);
                if(load == 1) // if graph exist
                {
                    if(mDIJKSTRA(vertex) == false) // DIJKSTRA ERROR
                    {
                        cout << "dijkstar Error " << endl;
                        printErrorCode(700);
                    }
                    else
                    {
                        fout << "==============================\n\n";
                    }
                }
                else
                {
                    printErrorCode(700);
                }
            }
            else if(word == "BELLMANFORD")  //  if word is "BELLMANFORD"
            {
                int vertex2 = 0;
                ptr = strtok(NULL, " ");
                
                if(ptr == NULL) // no start vertex
                {
                    printErrorCode(800);
                    continue;
                }
                
                path = ptr;        // input file directory

                path.erase(std::remove_if(path.begin(), path.end(), ::isspace), path.end());

                int vertex = stoi(path);
                
                ptr = strtok(NULL, "\n");
                
                if(ptr == NULL) // no end vertex
                {
                    printErrorCode(800);
                    continue;
                }
                path = ptr;
                
                vertex2 = stoi(path);
                
                if(load == 1) // if graph exist
                {
                    if(mBELLMANFORD(vertex, vertex2) == false) // BELLMANFORD ERROR
                    {
                        printErrorCode(800);
                    }
                    else
                    {
                        fout << "==============================\n\n";
                    }
                }
                else
                {
                    printErrorCode(800);
                }
            }
        }
    }
    fin.close();
}

bool Manager::LOAD(string filename) // LOAD function
{
    string line;
    ifstream in;
    in.open(filename);
    
    bool type;
    int size = 0;
    
    if(load == 1) // already exist graph
    {
        cout << "new " << endl;
        delete graph;
    }
    
    if(!in) // file open error
    {
        cout << "no" << endl;
        return false;
    }
    
    getline(in, line);
    
    if(!line.compare(""))       // ignore file end buffer
    {
        return false;
    }
    
//    cout << "LINE : " << line << endl;
    
    line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end()); // erase backspace
    
    if(line.compare("L") == 0)    // List graph
    {
        
        string t_size;
        type = 0;
        getline(in, t_size);
        
        size = stoi(t_size);
//        cout << size << endl;
        
        graph = new ListGraph(type, size); // create list graph
        
        char* ptr;
        char str_p[1000] = {0,};
        string path;
        strcpy(str_p,line.c_str());
        ptr = strtok(str_p, " ");
        
        int start = 0;
        int end = 0;
        int weight = 0;
        string data;
        
        while(!in.eof())
        {
            getline(in, data);
            if(!data.compare(""))       // ignore file end buffer
                break;
            if(data.length() == 1)
            {
                start = stoi(data);
            }
            else
            {
                char* ptr;
                char str_p[1000] = {0,};
                string path;
                strcpy(str_p,data.c_str());
                ptr = strtok(str_p, " ");
                end = stoi(ptr);
                ptr = strtok(NULL, " ");
                weight = stoi(ptr);
                graph->insertEdge(start, end, weight);
                
            }
        }
        
        fout << "========LOAD========\n";
        fout << "Success\n";
        
    }
    else if(line.compare("M") == 0) // matrix graph
    {
        string t_size;
        type = 1;
        getline(in, t_size);
        
        size = stoi(t_size);
        int weight = 0;
        
        
        graph = new MatrixGraph(type, size); // create matrix graph
        
        while(!in.eof())
        {
            for(int i = 0; i < size; i++)
            {
                string data;
                getline(in, data);
                if(!data.compare(""))       // ignore file end buffer
                    break;
                char* ptr;
                char str_p[1000] = {0,};
                string path;
                strcpy(str_p,data.c_str());
                
                ptr = strtok(str_p, " ");
                weight = stoi(ptr);
                graph->insertEdge(i, 0, weight);
                
                for(int j = 1; j < size-1; j++)
                {
                    ptr = strtok(NULL, " ");
                    weight = stoi(ptr);
                    graph->insertEdge(i, j, weight);
                }
                
                ptr = strtok(NULL, "\n");
                weight = stoi(ptr);
                graph->insertEdge(i, size-1, weight);
            }
        }
        fout << "========LOAD========\n";
        fout << "Success\n";
        
    }
    else
    {
        cout << "Error" << endl;
        return false;
    }
    
    return true;
}

bool Manager::PRINT() // print function
{
	if(graph->printGraph(&fout))
		return true;
	return false;
}

bool Manager::mBFS(int vertex) // bfs function
{
    if(BFS(graph, vertex, &fout))
        return true;
    return false;
}

bool Manager::mDFS(int vertex) // dfs function
{
    if(DFS(graph, vertex, &fout))
        return true;
    return false;
}


bool Manager::mDFS_R(int vertex) // dfs_r function
{
    int size = graph->getSize();
    map<int,int>* m = new map<int, int>[size];
    bool* visit = new bool[size];
    fill(visit, visit + size, false);
    
    if(DFS_R(graph, visit, vertex, m, &fout))
    {
        delete[] m;
        delete[] visit;
        return true;
    }
        
    m->clear();
    delete[] m;
    delete[] visit;
    
    return false;
}


bool Manager::mDIJKSTRA(int vertex) // dijkstra function
{
    if(Dijkstra(graph, vertex, &fout))
        return true;
    return false;
}

bool Manager::mKRUSKAL() // kruskal function
{
    if(Kruskal(graph, &fout))
    {
        return true;
    }
    return false;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex) // bellmanford
{
    if(Bellmanford(graph, s_vertex, e_vertex, &fout))
    {
        return true;
    }
    return false;
}
 
bool Manager::mFLOYD() // floyd function
{
    if(FLOYD(graph, &fout))
    {
        return true;
    }
    return false;
}

void Manager::printErrorCode(int n) // print error code
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"=======================\n"<<endl;
}
