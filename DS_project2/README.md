# Assignment 02 - Flight Management System

항공편 관리 프로그램

항공편 데이터를 B+ Tree, AVL Tree, Vector를 활용해 저장, 검색, 정렬, 출력하도록 구현했다. 항공편 번호를 기준으로 데이터를 관리하며, 명령어 파일을 읽어 각 기능을 수행하고 결과를 `log.txt`에 기록한다.

## 프로젝트 개요

이 프로그램은 `command.txt`에 작성된 명령어를 순서대로 읽고, 항공편 데이터를 관리한다.

전체적인 데이터 흐름은 다음과 같다.

```text id="z4upmz"
input_data.txt
   ↓ LOAD
B+ Tree
   ↓ ADD / SEARCH_BP / PRINT_BP
Flight Data Management
   ↓ 좌석 수 0 조건
AVL Tree
   ↓ VLOAD
Vector
   ↓ VPRINT
log.txt
```

B+ Tree는 항공편 데이터를 저장하고 검색하는 중심 자료구조로 사용했다. 항공편 번호를 기준으로 데이터를 정렬된 상태로 관리하며, 단일 검색과 범위 검색을 지원한다.

AVL Tree는 좌석 수가 0이 된 항공편을 따로 관리하기 위해 사용했다. 일반 이진 탐색 트리와 달리 삽입 후 균형을 유지하기 때문에 검색 성능을 안정적으로 유지할 수 있다.

Vector는 AVL Tree에 저장된 데이터를 가져와 특정 기준에 따라 정렬하고 출력하기 위해 사용했다.

## 주요 기능

### LOAD

`input_data.txt` 파일에서 항공편 데이터를 읽어 B+ Tree에 저장한다.

입력 데이터는 항공사명, 항공편 번호, 도착지, 좌석 수, 상태 정보를 가진다. 파일을 한 줄씩 읽고 각 필드를 분리한 뒤, `FlightData` 객체로 만들어 B+ Tree에 삽입한다.

### ADD

새로운 항공편 데이터를 추가하거나 기존 항공편의 상태와 좌석 정보를 갱신한다.

```text id="uqz27i"
ADD <flight_number> <airline_name> <status> <destination>
```

새로운 항공편이면 항공사명에 따라 초기 좌석 수를 설정한 뒤 B+ Tree에 삽입한다.

기존 항공편이면 상태 조건에 따라 좌석 수를 감소시키거나 상태 정보를 갱신한다. 좌석 수가 0이 되면 해당 항공편을 AVL Tree에도 삽입한다.

### PRINT_BP

B+ Tree에 저장된 전체 항공편 데이터를 출력한다.

B+ Tree의 가장 왼쪽 데이터 노드부터 시작해 연결된 데이터 노드를 순서대로 탐색한다. 이를 통해 항공편 번호 기준으로 정렬된 데이터를 확인할 수 있다.

### SEARCH_BP

B+ Tree에서 항공편 데이터를 검색한다.

```text id="sb53gy"
SEARCH_BP <flight_number>
SEARCH_BP <start_flight_number> <end_flight_number>
```

인자가 하나인 경우 특정 항공편 번호를 검색한다.
인자가 두 개인 경우 시작 항공편 번호부터 종료 항공편 번호까지의 범위 검색을 수행한다.

B+ Tree의 데이터 노드가 연결 리스트 형태로 이어져 있기 때문에 범위 검색을 처리하기에 적합하다.

### SEARCH_AVL

AVL Tree에서 특정 항공편 번호를 검색한다.

```text id="z642a3"
SEARCH_AVL <flight_number>
```

AVL Tree에는 좌석 수가 0이 된 항공편 데이터가 저장된다.
검색은 일반 이진 탐색 트리와 같은 방식으로 진행되지만, AVL Tree는 균형을 유지하므로 탐색 성능을 안정적으로 유지할 수 있다.

### VLOAD

AVL Tree에 저장된 항공편 데이터를 Vector로 불러온다.

AVL Tree를 중위 순회하여 데이터를 Vector에 저장하고, 이후 `VPRINT` 명령에서 정렬 기준에 따라 출력할 수 있도록 한다.

### VPRINT

Vector에 저장된 항공편 데이터를 조건에 따라 정렬해 출력한다.

```text id="vhh3t4"
VPRINT A
VPRINT B
```

`VPRINT A`는 항공사명, 도착지, 상태 기준으로 정렬한다.
`VPRINT B`는 도착지, 상태, 항공사명 기준으로 정렬한다.

### EXIT

프로그램을 종료한다.

프로그램 실행 결과는 `log.txt`에 기록된다.

## 사용한 자료구조

| 자료구조     | 사용 위치                          | 역할                                 |
| -------- | ------------------------------ | ---------------------------------- |
| B+ Tree  | LOAD, ADD, PRINT_BP, SEARCH_BP | 항공편 데이터를 항공편 번호 기준으로 저장, 검색, 범위 검색 |
| AVL Tree | ADD, SEARCH_AVL, VLOAD         | 좌석 수가 0인 항공편 데이터를 균형 트리로 관리        |
| Vector   | VLOAD, VPRINT                  | AVL Tree 데이터를 임시 저장하고 조건별 정렬 출력    |
| Map      | B+ Tree Node                   | 노드 내부에서 키와 데이터를 정렬된 형태로 저장         |

## 명령어 목록

| 명령어        | 설명                                        |
| ---------- | ----------------------------------------- |
| LOAD       | `input_data.txt` 파일의 항공편 데이터를 B+ Tree에 저장 |
| ADD        | 항공편 데이터를 추가하거나 기존 항공편 상태를 갱신              |
| PRINT_BP   | B+ Tree에 저장된 전체 항공편 데이터 출력                |
| SEARCH_BP  | B+ Tree에서 특정 항공편 또는 항공편 번호 범위 검색          |
| SEARCH_AVL | AVL Tree에서 좌석 수가 0인 항공편 검색                |
| VLOAD      | AVL Tree 데이터를 Vector로 불러오기                |
| VPRINT     | Vector 데이터를 조건에 따라 정렬 출력                  |
| EXIT       | 프로그램 종료                                   |

## 에러 코드

| 에러 코드 | 발생 상황                                |
| ----- | ------------------------------------ |
| 100   | LOAD 명령어 오류, 파일 열기 실패, 입력 데이터 형식 오류  |
| 200   | VLOAD 명령어 오류 또는 불러올 데이터가 없는 경우       |
| 300   | ADD 명령어 오류, 항공편 정보 형식 오류, 상태 변경 불가   |
| 400   | SEARCH_BP 명령어 오류 또는 검색 결과가 없는 경우     |
| 500   | SEARCH_AVL 명령어 오류 또는 검색 결과가 없는 경우    |
| 600   | VPRINT 명령어 오류 또는 출력할 데이터가 없는 경우      |
| 700   | PRINT_BP 명령어 오류 또는 B+ Tree가 비어 있는 경우 |
| 800   | 존재하지 않는 명령어                          |

## 파일 구성

```text id="jfn82w"
Assignment02_FlightManager/
├── README.md
├── Report_DS_project2.pdf
├── main.cpp
├── Manager.cpp
├── Manager.h
├── FlightData.h
├── BpTree.cpp
├── BpTree.h
├── BpTreeNode.h
├── BpTreeDataNode.h
├── BpTreeIndexNode.h
├── AVLTree.cpp
├── AVLTree.h
└── AVLNode.h
```

## 실행 방법

### Compile

```bash id="i54l9i"
g++ -std=c++17 *.cpp -o flight_manager
```

### Run

```bash id="yw60xh"
./flight_manager
```

프로그램 실행 시 같은 경로에 `command.txt`와 `input_data.txt`가 있어야 한다.

```text id="jok9nh"
command.txt
input_data.txt
```

`main.cpp`에서는 `manager.run("command.txt")`를 호출하므로, 기본 명령어 파일명은 `command.txt`이다.

## 예시 명령어

```text id="bvrxl9"
LOAD
PRINT_BP
ADD	KE123	KoreanAir	Boarding	ICN
SEARCH_BP	KE123
SEARCH_BP	AA000	ZZ999
SEARCH_AVL	KE123
VLOAD
VPRINT	A
VPRINT	B
EXIT
```

명령어와 인자는 탭(tab)으로 구분한다.

## 구현 포인트

이 과제에서는 B+ Tree와 AVL Tree를 서로 다른 목적에 맞게 나누어 사용했다.

B+ Tree는 전체 항공편 데이터를 관리하는 중심 자료구조이다. 항공편 번호를 키로 사용하고, 데이터 노드에는 실제 항공편 정보를 저장한다. 노드에 저장 가능한 데이터 수를 초과하면 데이터 노드를 분할하고, 필요한 경우 인덱스 노드까지 분할하여 트리의 구조를 유지한다.

AVL Tree는 좌석 수가 0이 된 항공편을 관리하기 위해 사용했다. 삽입 후 균형 인수를 계산하고, 균형이 깨졌을 경우 LL, RR, LR, RL 상황에 따라 회전을 수행한다. 이를 통해 트리 높이가 한쪽으로 치우치지 않도록 유지한다.

Vector는 AVL Tree에 저장된 데이터를 정렬 출력하기 위해 사용했다. Tree 구조는 검색에는 유리하지만 여러 조건을 조합한 정렬 출력에는 Vector가 더 다루기 쉽기 때문에, AVL Tree의 데이터를 Vector로 옮긴 뒤 정렬 기준에 따라 출력하도록 구성했다.

## 항공편 데이터 구조

각 항공편 데이터는 다음 정보를 가진다.

| 필드           | 설명      |
| ------------ | ------- |
| AirlineName  | 항공사명    |
| FlightNumber | 항공편 번호  |
| Destination  | 도착지     |
| Seats        | 잔여 좌석 수 |
| Status       | 항공편 상태  |

## 보고서

과제 구현 과정, 흐름도, 알고리즘 설명, 실행 결과, 예외 처리 내용은 보고서에 정리되어 있다.

```text id="h62ccx"
Report_DS_project2.pdf
```

## 배운 점

이번 과제를 통해 B+ Tree와 AVL Tree를 실제 프로그램 흐름 안에서 사용하는 경험을 할 수 있었다.

B+ Tree를 구현하면서 데이터 노드와 인덱스 노드를 나누고, 노드가 초과되었을 때 분할을 수행하는 과정을 익혔다. 특히 데이터 노드를 연결해 범위 검색을 처리하는 방식이 왜 B+ Tree에서 중요한지 이해할 수 있었다.

AVL Tree를 구현하면서 균형 인수와 회전 연산의 필요성을 직접 확인했다. 단순한 이진 탐색 트리는 입력 순서에 따라 한쪽으로 치우칠 수 있지만, AVL Tree는 삽입 후 균형을 유지하기 때문에 검색 성능을 안정적으로 유지할 수 있다.

또한 명령어 기반으로 프로그램을 구성하면서 파일 입력, 명령어 파싱, 예외 처리, 로그 출력이 자료구조 구현만큼 중요하다는 점을 느꼈다. 단순히 자료구조를 만드는 것에서 끝나는 것이 아니라, 여러 자료구조를 어떤 기준으로 나누어 사용할지 설계하는 과정이 중요하다는 것을 배웠다.
