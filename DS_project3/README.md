# Assignment 03 - Graph Algorithm Manager

데이터구조설계 3차 과제로 진행한 C++ 기반 그래프 알고리즘 프로그램이다.

그래프 데이터를 인접 리스트와 인접 행렬 방식으로 저장하고, BFS, DFS, Kruskal, Dijkstra, Bellman-Ford, Floyd-Warshall 알고리즘을 명령어 기반으로 실행하도록 구현했다.

## 프로젝트 개요

이 프로그램은 `command.txt`에 작성된 명령어를 순서대로 읽고, 그래프 파일을 불러온 뒤 각 그래프 알고리즘을 수행한다.

전체적인 흐름은 다음과 같다.

```text id="uob6zf"
command.txt
   ↓
LOAD graph file
   ↓
ListGraph or MatrixGraph
   ↓
PRINT / BFS / DFS / DFS_R
KRUSKAL / DIJKSTRA / BELLMANFORD / FLOYD
   ↓
log.txt
```

그래프 입력 파일의 첫 줄이 `L`이면 인접 리스트 기반 `ListGraph`를 생성하고, `M`이면 인접 행렬 기반 `MatrixGraph`를 생성한다.

`ListGraph`는 간선이 비교적 적은 그래프를 표현하기에 적합하고, `MatrixGraph`는 정점 간 연결 정보를 행렬 형태로 빠르게 확인할 수 있다는 특징이 있다.

## 주요 기능

### LOAD

그래프 데이터를 파일에서 읽어온다.

```text id="xww3mc"
LOAD <graph_file>
```

입력 파일의 첫 줄에 따라 그래프 표현 방식을 결정한다.

```text id="dmgs7z"
L: ListGraph
M: MatrixGraph
```

그래프 크기를 읽은 뒤, 각 정점과 간선의 가중치 정보를 저장한다.

### PRINT

현재 저장된 그래프를 출력한다.

ListGraph인 경우 각 정점에 연결된 인접 정점과 가중치를 출력한다.
MatrixGraph인 경우 인접 행렬 형태로 전체 그래프를 출력한다.

### BFS

너비 우선 탐색(Breadth-First Search, BFS)을 수행한다.

```text id="efr4sq"
BFS <start_vertex>
```

시작 정점에서 가까운 정점부터 차례대로 방문한다. Queue를 사용해 탐색 순서를 관리한다.

### DFS

깊이 우선 탐색(Depth-First Search, DFS)을 수행한다.

```text id="n109wx"
DFS <start_vertex>
```

시작 정점에서 가능한 깊게 탐색한 뒤, 더 이상 갈 수 없으면 이전 정점으로 돌아간다. Stack을 사용해 비재귀 방식으로 구현했다.

### DFS_R

재귀 기반 깊이 우선 탐색을 수행한다.

```text id="jddor0"
DFS_R <start_vertex>
```

DFS와 같은 깊이 우선 탐색이지만, 명시적인 Stack 대신 재귀 호출을 사용한다.

### KRUSKAL

Kruskal 알고리즘을 사용해 최소 신장 트리(Minimum Spanning Tree, MST)를 구한다.

```text id="sx2ww3"
KRUSKAL
```

모든 간선을 가중치 기준으로 정렬한 뒤, 가중치가 작은 간선부터 선택한다. 이때 사이클이 생기지 않도록 Union-Find 구조를 사용한다.

### DIJKSTRA

Dijkstra 알고리즘을 사용해 특정 시작 정점에서 다른 모든 정점까지의 최단 경로를 구한다.

```text id="r6fmdu"
DIJKSTRA <start_vertex>
```

방문하지 않은 정점 중 현재 거리가 가장 짧은 정점을 선택하고, 인접 정점의 거리를 갱신하는 방식으로 동작한다.

단, Dijkstra 알고리즘은 음수 가중치가 있는 그래프에는 적합하지 않다.

### BELLMANFORD

Bellman-Ford 알고리즘을 사용해 시작 정점에서 도착 정점까지의 최단 경로를 구한다.

```text id="kyja5p"
BELLMANFORD <start_vertex> <end_vertex>
```

모든 간선을 반복적으로 확인하면서 최단 거리를 갱신한다. 음수 가중치가 있는 그래프도 처리할 수 있으며, 음수 사이클이 존재하는 경우 오류로 처리한다.

### FLOYD

Floyd-Warshall 알고리즘을 사용해 모든 정점 쌍 사이의 최단 경로를 구한다.

```text id="ooqbub"
FLOYD
```

동적 계획법을 이용해 중간 정점을 하나씩 고려하면서 모든 정점 간 최단 거리를 갱신한다.

## 사용한 자료구조와 알고리즘

| 구분         | 사용 위치        | 역할                 |
| ---------- | ------------ | ------------------ |
| 인접 리스트     | ListGraph    | 정점별 인접 간선 저장       |
| 인접 행렬      | MatrixGraph  | 정점 간 연결 정보를 행렬로 저장 |
| Queue      | BFS          | 너비 우선 탐색 순서 관리     |
| Stack      | DFS          | 깊이 우선 탐색 순서 관리     |
| Recursion  | DFS_R        | 재귀 기반 깊이 우선 탐색     |
| Union-Find | Kruskal      | 사이클 여부 확인          |
| Vector     | 경로 출력, 간선 저장 | 탐색 결과와 간선 정보 저장    |
| Map        | 인접 간선 관리     | 정점과 가중치 저장         |

## 명령어 목록

| 명령어                   | 설명                                     |
| --------------------- | -------------------------------------- |
| LOAD file             | 그래프 파일을 읽어 ListGraph 또는 MatrixGraph 생성 |
| PRINT                 | 현재 그래프 출력                              |
| BFS vertex            | 시작 정점 기준 BFS 수행                        |
| DFS vertex            | 시작 정점 기준 DFS 수행                        |
| DFS_R vertex          | 시작 정점 기준 재귀 DFS 수행                     |
| KRUSKAL               | 최소 신장 트리 계산                            |
| DIJKSTRA vertex       | 시작 정점 기준 최단 경로 계산                      |
| BELLMANFORD start end | 시작 정점에서 도착 정점까지 최단 경로 계산               |
| FLOYD                 | 모든 정점 쌍의 최단 경로 계산                      |
| EXIT                  | 프로그램 종료                                |

## 에러 코드

| 에러 코드 | 발생 상황                       |
| ----- | --------------------------- |
| 100   | LOAD 명령어 오류 또는 그래프 파일 열기 실패 |
| 200   | PRINT 명령어 오류 또는 그래프가 없는 경우  |
| 300   | BFS 명령어 오류                  |
| 400   | DFS 명령어 오류                  |
| 500   | DFS_R 명령어 오류                |
| 600   | KRUSKAL 명령어 오류              |
| 700   | DIJKSTRA 명령어 오류             |
| 800   | BELLMANFORD 명령어 오류          |
| 900   | FLOYD 명령어 오류                |

## 파일 구성

```text id="jsgm1h"
Assignment03_GraphAlgorithms/
├── README.md
├── Report_DS_project3.pdf
├── main.cpp
├── Manager.cpp
├── Manager.h
├── Graph.cpp
├── Graph.h
├── GraphMethod.cpp
├── GraphMethod.h
├── ListGraph.cpp
├── ListGraph.h
├── MatrixGraph.cpp
└── MatrixGraph.h
```

## 실행 방법

### Compile

```bash id="xin7cf"
g++ -std=c++17 *.cpp -o graph_manager
```

### Run

```bash id="eownnn"
./graph_manager
```

프로그램 실행 시 같은 경로에 `command.txt`와 그래프 입력 파일이 있어야 한다.

예시는 다음과 같다.

```text id="r502y6"
command.txt
graph_L.txt
graph_M.txt
```

`main.cpp`에서는 `ds.run("command.txt")`를 호출하므로, 기본 명령어 파일명은 `command.txt`이다.

## 예시 명령어

```text id="kpv7tf"
LOAD graph_M.txt
PRINT
LOAD graph_L.txt
PRINT
BFS 0
DFS 2
DFS_R 2
KRUSKAL
DIJKSTRA 5
BELLMANFORD 0 6
FLOYD
EXIT
```

## 그래프 입력 형식

### ListGraph 입력 예시

```text id="w88bfc"
L
7
0
1 6
2 2
1
3 5
2
1 7
4 3
5 8
```

첫 줄은 그래프 타입이다.
두 번째 줄은 정점 개수이다.
이후에는 시작 정점과 연결된 도착 정점, 가중치 정보를 입력한다.

### MatrixGraph 입력 예시

```text id="oj60fi"
M
7
0 6 2 0 0 0 0
0 0 0 5 0 0 0
0 7 0 0 3 8 0
0 0 0 0 0 0 3
0 0 0 4 0 0 0
0 0 0 0 0 0 1
0 0 0 0 10 0 0
```

첫 줄은 그래프 타입이다.
두 번째 줄은 정점 개수이다.
이후에는 인접 행렬 형태로 간선의 가중치를 입력한다. 연결되지 않은 경우 0으로 표시한다.

## 구현 포인트

이 과제에서는 그래프 표현 방식과 그래프 알고리즘을 분리해서 구현했다.

`Graph` 클래스를 기반으로 `ListGraph`와 `MatrixGraph`를 나누어 구현했고, 알고리즘 함수들은 `Graph*`를 인자로 받아 동일한 방식으로 실행되도록 구성했다. 이를 통해 그래프가 인접 리스트 방식인지 인접 행렬 방식인지와 관계없이 BFS, DFS, 최단 경로 알고리즘을 실행할 수 있다.

BFS는 Queue를 사용해 가까운 정점부터 방문하도록 구현했다. DFS는 Stack을 사용하는 비재귀 방식과 재귀 호출을 사용하는 방식으로 나누어 구현했다.

Kruskal 알고리즘에서는 간선을 가중치 기준으로 정렬하고, Union-Find를 사용해 사이클 생성을 방지했다. Dijkstra, Bellman-Ford, Floyd-Warshall은 각각 단일 시작점 최단 경로, 음수 가중치 처리 가능 최단 경로, 모든 정점 쌍 최단 경로 계산을 위해 구현했다.

## 보고서

과제 구현 과정, 흐름도, 알고리즘 설명, 실행 결과는 보고서에 정리되어 있다.

```text id="fe46tr"
Report_DS_project3.pdf
```

## 배운 점

이번 과제를 통해 그래프를 인접 리스트와 인접 행렬로 각각 구현하며 두 표현 방식의 차이를 이해할 수 있었다.

또한 BFS, DFS, Kruskal, Dijkstra, Bellman-Ford, Floyd-Warshall 알고리즘을 직접 구현하면서 그래프 탐색, 최소 신장 트리, 최단 경로 문제의 동작 방식을 코드 수준에서 익힐 수 있었다.
