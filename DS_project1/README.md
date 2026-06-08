# Assignment 01 - Subtitle Manager

데이터구조설계 1차 과제로 진행한 C++ 기반 자막 관리 프로그램이다.

자막 파일에서 시간 정보와 자막 내용을 읽어온 뒤, Queue, Binary Search Tree, Linked List를 활용해 자막 데이터를 저장, 정렬, 조회, 구간 관리, 삭제하도록 구현했다.

## 프로젝트 개요

이 프로그램은 `command.txt`에 작성된 명령어를 순서대로 읽고, 각 명령어에 따라 자막 데이터를 처리한다.

전체적인 데이터 흐름은 다음과 같다.

```text
subtitle.txt
   ↓ LOAD
Queue
   ↓ QPOP
Binary Search Tree
   ↓ PRINT / SECTION / DELETE
Section List
   ↓ PRINT N
log.txt
```

자막 데이터는 먼저 Queue에 저장된다. 이후 `QPOP` 명령을 통해 Queue에 있던 데이터가 Binary Search Tree로 이동한다.

BST에 저장된 자막은 시간 값을 기준으로 정렬된다. 따라서 중위 순회 방식으로 출력하면 자막을 시간순으로 확인할 수 있다.

또한 특정 시간 범위에 해당하는 자막은 Section List로 따로 저장할 수 있다. 이를 통해 전체 자막뿐 아니라 특정 구간의 자막만 따로 조회할 수 있다.

## 주요 기능

### LOAD

`subtitle.txt` 파일에서 자막 데이터를 읽어 Queue에 저장한다.

각 줄에서 첫 번째 값은 자막 시간으로, 나머지 문자열은 자막 내용으로 분리한다. Queue는 선입선출 구조이기 때문에 입력 파일에서 읽은 순서대로 데이터가 저장된다.

### QPOP

Queue에 저장된 모든 자막 데이터를 하나씩 꺼내 Binary Search Tree에 삽입한다.

자막 시간 값을 기준으로 BST에 삽입되며, 이후 검색, 정렬 출력, 삭제 기능을 수행할 수 있다.

### PRINT

BST에 저장된 전체 자막 데이터를 출력한다.

BST를 중위 순회하면 왼쪽 서브트리, 현재 노드, 오른쪽 서브트리 순서로 방문한다. 이 특성을 이용해 자막 데이터를 시간순으로 출력한다.

### SECTION

특정 시간 구간에 해당하는 자막 데이터를 찾아 Section List에 저장한다.

```text
SECTION <section_number> <start_time> <end_time>
```

BST에서 시작 시간과 종료 시간 사이에 포함되는 자막을 탐색한 뒤, 해당 데이터들을 Linked List 형태로 연결한다.

### PRINT N

특정 섹션 번호에 해당하는 자막 목록을 출력한다.

```text
PRINT <section_number>
```

이전에 `SECTION` 명령으로 만들어둔 섹션이 존재하면, 해당 섹션에 저장된 자막들을 순서대로 출력한다.

### DELETE

BST에 저장된 자막 데이터를 시간 기준으로 삭제한다.

```text
DELETE EQUAL <time>
DELETE UNDER <time>
```

`DELETE EQUAL`은 입력한 시간과 정확히 일치하는 자막 하나를 삭제한다.

`DELETE UNDER`는 입력한 시간보다 이전에 해당하는 자막들을 삭제한다. 기준 시간과 같은 자막은 삭제 대상에 포함하지 않는다.

### EXIT

프로그램을 종료한다.

프로그램 종료 전 동적 할당된 자료구조를 해제하고, 실행 결과를 `log.txt`에 출력한다.

## 사용한 자료구조

| 자료구조               | 사용 위치                        | 역할                            |
| ------------------ | ---------------------------- | ----------------------------- |
| Queue              | LOAD, QPOP                   | 자막 데이터를 입력 순서대로 임시 저장         |
| Binary Search Tree | QPOP, PRINT, SECTION, DELETE | 자막 시간을 기준으로 삽입, 검색, 정렬 출력, 삭제 |
| Linked List        | SECTION, PRINT N             | 특정 시간 범위의 자막을 섹션 단위로 저장       |

## 명령어 목록

| 명령어                 | 설명                              |
| ------------------- | ------------------------------- |
| LOAD                | `subtitle.txt` 파일을 읽어 Queue에 저장 |
| QPOP                | Queue의 모든 데이터를 BST에 삽입          |
| PRINT               | BST에 저장된 전체 자막 출력               |
| PRINT N             | N번 섹션에 저장된 자막 출력                |
| SECTION N start end | start부터 end까지의 자막을 N번 섹션으로 저장   |
| DELETE EQUAL time   | time과 일치하는 자막 삭제                |
| DELETE UNDER time   | time보다 이전의 자막 삭제                |
| EXIT                | 프로그램 종료                         |

## 에러 코드

| 에러 코드 | 발생 상황                                  |
| ----- | -------------------------------------- |
| 100   | LOAD 명령어 오류 또는 `subtitle.txt` 파일 열기 실패 |
| 200   | QPOP 명령어 오류 또는 Queue가 비어 있는 경우         |
| 300   | PRINT 명령어 오류, BST가 비어 있거나 섹션이 없는 경우    |
| 400   | SECTION 명령어 오류 또는 해당 시간 범위의 자막이 없는 경우  |
| 500   | DELETE 명령어 오류 또는 삭제할 대상이 없는 경우         |
| 1000  | 존재하지 않는 명령어 또는 EXIT 명령어 오류             |

## 파일 구성

```text
Assignment01_SubtitleManager/
├── README.md
├── Report_DS_project1.pdf
├── main.cpp
├── Manager.cpp
├── Manager.h
├── SubtitleQueue.cpp
├── SubtitleQueue.h
├── SubtitleQueueNode.h
├── SubtitleBST.cpp
├── SubtitleBST.h
├── SubtitleBSTNode.h
├── SectionList.cpp
├── SectionList.h
├── SectionListNode.h
└── SubtitleListNode.h
```

## 실행 방법

### Compile

```bash
g++ -std=c++17 *.cpp -o subtitle_manager
```

### Run

```bash
./subtitle_manager
```

프로그램 실행 시 같은 경로에 `command.txt`와 `subtitle.txt`가 있어야 한다.

```text
command.txt
subtitle.txt
```

`main.cpp`에서는 `Manager.Run("command.txt")`를 호출하므로, 기본 명령어 파일명은 `command.txt`이다.

## 예시 명령어

```text
LOAD
QPOP
PRINT
SECTION 3 00:52:10 00:52:30
SECTION 2 00:53:50 00:54:23
PRINT 3
PRINT 2
DELETE EQUAL 00:52:36
PRINT
DELETE UNDER 00:52:23
PRINT
PRINT 3
EXIT
```

## 구현 포인트

이 과제에서는 자료구조를 각각 따로 구현하는 것에서 끝나지 않고, 여러 자료구조가 하나의 흐름 안에서 이어지도록 구성했다.

먼저 `LOAD` 명령을 통해 자막 데이터를 Queue에 저장한다. 이후 `QPOP` 명령으로 Queue의 데이터를 BST에 삽입한다. BST는 자막 시간을 기준으로 데이터를 저장하므로, 중위 순회를 통해 시간순 출력이 가능하다.

`SECTION` 기능은 BST에서 특정 시간 범위에 포함되는 자막을 찾아 별도의 Linked List로 저장한다. 이때 섹션 데이터는 BST의 노드를 직접 연결하는 방식이 아니라, 새로운 리스트 노드로 복사해 저장하는 방식으로 구성했다. 따라서 이후 BST에서 일부 자막이 삭제되더라도, 이미 만들어진 섹션의 데이터는 유지된다.

`DELETE` 기능에서는 BST 삭제 로직을 구현했다. 삭제 대상 노드가 자식 노드를 가지지 않는 경우, 하나의 자식 노드만 가지는 경우, 두 개의 자식 노드를 가지는 경우를 나누어 처리했다. 특히 자식 노드가 두 개인 경우에는 오른쪽 서브트리에서 가장 작은 값을 찾아 삭제 대상 노드를 대체하도록 구현했다.

## 보고서

과제 구현 과정, 흐름도, 알고리즘 설명, 실행 결과, 예외 테스트 내용은 보고서에 정리되어 있다.

```text
Report_DS_project1.pdf
```

## 배운 점

이번 과제를 통해 Queue, Binary Search Tree, Linked List의 동작 원리를 직접 구현하며 익힐 수 있었다.

특히 BST의 삽입, 검색, 중위 순회, 삭제 로직을 구현하면서 포인터 기반 자료구조의 연결 관계를 더 깊게 이해할 수 있었다.

또한 명령어 파일을 읽어 프로그램 흐름을 제어하고, 실행 결과를 로그 파일로 출력하면서 자료구조가 실제 프로그램 안에서 어떻게 연결되어 동작하는지 경험할 수 있었다.
과제 진행 중에는 Windows Visual Studio 환경과 Ubuntu 환경에서의 컴파일 차이도 경험했다. 특히 클래스 이름과 객체 이름이 겹쳤을 때 환경에 따라 문제가 다르게 나타날 수 있다는 점을 알게 되었고, 명확한 이름 설계의 중요성을 느꼈다.
