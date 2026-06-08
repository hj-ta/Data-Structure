# DataStructure

2024년 2학기 데이터구조설계 수업에서 진행한 C++ 과제들을 정리한 저장소이다.

각 과제는 Queue, Binary Search Tree, B+ Tree, AVL Tree, Graph 등 주요 자료구조를 직접 구현하고, 이를 활용한 프로그램을 만들었다.


## Projects

| Assignment | Description                                            |
| ---------- | ------------------------------------------------------ |
| 1차 과제      | Queue, Binary Search Tree, Linked List를 활용한 자막 관리 프로그램 |
| 2차 과제      | B+ Tree, AVL Tree, Vector를 활용한 항공편 관리 프로그램             |
| 3차 과제      | 리스트, 행렬 기반 그래프 알고리즘 프로그램                         |



## Assignment 01 - Subtitle Manager

자막 데이터를 관리하는 프로그램이다.

`subtitle.txt` 파일에서 자막 시간과 내용을 읽어오고, Queue에 임시 저장한 뒤 Binary Search Tree에 삽입해 시간순으로 관리한다. 특정 시간 범위의 자막은 Linked List 기반의 Section List로 따로 저장할 수 있다.

주요 기능

* 자막 데이터 로드
* Queue 기반 임시 저장
* BST 기반 시간순 정렬 및 출력
* 특정 시간 구간 Section 생성
* 특정 자막 또는 특정 시간 이전 자막 삭제

## Assignment 02 - Flight Management System

항공편 데이터를 관리하는 프로그램.

항공편 번호를 기준으로 B+ Tree에 데이터를 저장하고, 좌석 수가 0이 된 항공편은 AVL Tree로 관리한다. AVL Tree에 저장된 데이터는 Vector로 불러와 조건에 따라 정렬 출력할 수 있다.

주요 기능

* 항공편 데이터 로드
* 항공편 추가 및 상태 갱신
* B+ Tree 기반 단일 검색 및 범위 검색
* AVL Tree 기반 좌석 수 0 항공편 검색
* Vector 기반 조건별 정렬 출력

## Assignment 03 - Graph Algorithm Manager

그래프 데이터를 기반으로 여러 그래프 알고리즘을 실행하는 프로그램이다.

그래프는 입력 파일에 따라 인접 리스트 또는 인접 행렬 방식으로 저장된다. 이후 명령어에 따라 그래프 출력, 탐색, 최소 신장 트리, 최단 경로 알고리즘을 수행한다.

주요 기능

* ListGraph, MatrixGraph 기반 그래프 저장
* BFS, DFS, DFS_R 탐색
* Kruskal 최소 신장 트리 계산
* Dijkstra 단일 시작점 최단 경로 계산
* Bellman-Ford 최단 경로 계산
* Floyd-Warshall 모든 정점 쌍 최단 경로 계산



