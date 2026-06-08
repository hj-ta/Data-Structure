#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"


bool BFS(Graph* graph, int vertex, ofstream* fout); // BFS
bool DFS(Graph* graph, int vertex, ofstream* fout); // DFS
bool DFS_R(Graph* graph, bool* visit,  int vertex, map<int, int>* m, ofstream* fout); //DFS_R
bool Kruskal(Graph* graph, ofstream* fout); // KRUSKAL
bool Dijkstra(Graph* graph, int vertex, ofstream* fout); // DIJKSTRA
bool Bellmanford(Graph* graph, int s_vertex, int e_vertex, ofstream* fout); // BELLMANFORD
bool FLOYD(Graph* graph, ofstream* fout); //FLOYD

int Find(int parent[], int vertex); // Find function
void Union(int parent[], int vertex1, int vertex2); // Union function

bool dfs_re(Graph* graph, bool* visit, int vertex,  map<int, int>* m, vector<int>* v); // dfs recursive function

void insert(int e, int* arr, int i); // for insert sort
void insertion(int* arr, int one, int two); // for insert sort
void quicksort(int* arr, int low, int high); // quick sort function

#endif
