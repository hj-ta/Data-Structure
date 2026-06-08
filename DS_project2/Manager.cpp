#include "Manager.h"
#include <sstream>
#include <algorithm>

using namespace std;

Manager::Manager(int bpOrder) {
    avl = new AVLTree();        // AVL Tree 초기화
    ofstream* fout = new ofstream("log.txt", ios::app);
    bp = new BpTree(fout, bpOrder);  // B+ Tree 초기화
}

Manager::~Manager() {
    delete avl;
    delete bp;
}

void Manager::run(const char* command_txt) {
    ifstream fin(command_txt);
    ofstream fout("log.txt", ios::app);

    if (!fin.is_open()) {
        printErrorCode(100);
        return;
    }

    string line;
    while (getline(fin, line)) {
        if (!line.empty() && line[line.length() - 1] == '\r') {
            line.erase(line.length() - 1); // Windows 줄바꿈 처리
        }
        if (line.empty()) continue;

        vector<string> split;
        stringstream sstr(line);
        string token;

        while (getline(sstr, token, '\t')) {
            if (!token.empty()) {
                split.push_back(token);
            }
        }

        if (split.empty()) continue;

        string command = split[0];

        if (command == "LOAD") {
            if (split.size() != 1) {
                printErrorCode(100);
            }
            else if (LOAD()) {
                PrintSuccess("LOAD");
            }
        }
        else if (command == "PRINT_BP") {
            if (PRINT_BP()) {
                PrintSuccess("PRINT_BP");
            }
            else {
                printErrorCode(700);
            }
        }
        else if (command == "ADD") {
            if (split.size() != 5) {
                printErrorCode(300);
            }
            else {
                if (ADD(split[1], split[2], split[3], split[4])) {
                    PrintSuccess("ADD");
                }
                else {
                    printErrorCode(300);
                }
            }
        }
        else if (command == "SEARCH_BP") {
            if (split.size() == 2 && SEARCH_BP(split[1])) {
                PrintSuccess("SEARCH_BP");
            }
            else if (split.size() == 3 && SEARCH_BP(split[1], split[2])) {
                PrintSuccess("SEARCH_BP");
            }
            else {
                printErrorCode(400);
            }
        }
        else if (command == "SEARCH_AVL") {
            if (split.size() == 2 && SEARCH_AVL(split[1])) {
                PrintSuccess("SEARCH_AVL");
            }
            else {
                printErrorCode(500);
            }
        }
        else if (command == "VLOAD") {
            if (VLOAD()) {
                PrintSuccess("VLOAD");
            }
            else {
                printErrorCode(200);
            }
        }
        else if (command == "VPRINT") {
            if (split.size() == 2 && VPRINT(split[1])) {
                PrintSuccess("VPRINT");
            }
            else {
                printErrorCode(600);
            }
        }
        else if (command == "EXIT") {
            PrintSuccess("EXIT");
            break;
        }
        else {
            printErrorCode(800); // Unknown command
        }
    }

    fin.close();
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" ");
    if (first == string::npos) return ""; // 공백만 있는 경우
    size_t last = str.find_last_not_of(" ");
    return str.substr(first, (last - first + 1));
}

bool Manager::LOAD() {
    // B+ Tree가 이미 초기화된 경우 에러 처리
    if (bp->getRoot() != nullptr) {
        printErrorCode(100); // 이미 초기화된 경우
        return false;
    }

    ifstream input_txt("input_data.txt");
    if (!input_txt.is_open()) { // 파일 열기 실패 시 에러 처리
        printErrorCode(100); // 파일 열기 실패
        return false;
    }

    string line;
    while (getline(input_txt, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;

        // 데이터 필드 분리
        while (getline(ss, field, ' ')) {
            fields.push_back(field);
        }

        if (fields.size() != 5) { // 필드 개수가 맞지 않을 경우 에러 처리
            printErrorCode(100); // 데이터 형식 오류
            continue;
        }

        try {
            // FlightData 생성 및 필드 설정
            FlightData* newData = new FlightData();
            newData->SetAirlineName(fields[0]);
            newData->SetFlightNumber(fields[1]);
            newData->SetDestination(fields[2]);
            newData->SetNumberofSeats(stoi(fields[3])); // 좌석 수 변환
            newData->SetStatus(fields[4]);

            // B+ Tree에 삽입
            if (!bp->Insert(newData)) {
                delete newData; // 삽입 실패 시 메모리 해제
                printErrorCode(100); // 삽입 실패
                continue;
            }
        }
        catch (...) { // 변환 실패 또는 예외 발생 시 에러 처리
            printErrorCode(100); // 예외 처리
            continue;
        }
    }

    input_txt.close();

    // 성공 메시지 출력
    PrintSuccess("LOAD");
    return true;
}



bool Manager::VLOAD() {
    if (Print_vector.empty()) return false;
    avl->GetVector(Print_vector);
    return true;
}
bool Manager::ADD(string flightNum, string airlineName, string flightStatus, string flightDestination) {
    // 항공편명 검증
    if (flightNum.size() != 5 || !std::all_of(flightNum.begin(), flightNum.end(), [](char c) { return std::isalnum(c) && std::isupper(c); })) {
        printErrorCode(300); // 잘못된 항공편명
        return false;
    }

    // 도착지명 검증
    if (flightDestination.size() != 3 || !std::all_of(flightDestination.begin(), flightDestination.end(), ::isupper)) {
        printErrorCode(300); // 잘못된 도착지명
        return false;
    }

    // "JEJU" 항공사의 경우 도착지 검증
    if (airlineName == "JEJU" && flightDestination != "CJU") {
        printErrorCode(300); // JEJU의 도착지가 CJU가 아닌 경우
        return false;
    }

    // B+ 트리에서 기존 데이터 검색
    FlightData* existingData = bp->findFlightData(flightNum);
    if (!existingData) { // 새 항공편 추가
        FlightData* newFlight = new FlightData();
        newFlight->SetAirlineName(airlineName);
        newFlight->SetFlightNumber(flightNum);
        newFlight->SetDestination(flightDestination);
        newFlight->SetStatus(flightStatus);

        // 항공사별 좌석 수 설정
        if (airlineName == "KoreanAir" || airlineName == "ASIANA")
            newFlight->SetNumberofSeats(7);
        else if (airlineName == "JEJU" || airlineName == "JeanAir")
            newFlight->SetNumberofSeats(5);
        else if (airlineName == "AirKwangwoon")
            newFlight->SetNumberofSeats(6);
        else {
            printErrorCode(300); // 잘못된 항공사명
            delete newFlight;
            return false;
        }

        // B+ 트리에 데이터 삽입
        if (!bp->Insert(newFlight)) {
            delete newFlight;
            printErrorCode(300); // 삽입 실패
            return false;
        }
    }
    else { // 기존 항공편 상태 업데이트
        if (flightStatus == "Boarding") {
            if (existingData->GetStatus() == "Boarding" || existingData->GetStatus() == "Cancelled") {
                existingData->SetSeatsDec(); // 좌석 수 감소
            }
            else {
                printErrorCode(300); // 상태 변경 불가능
                return false;
            }
        }
        else if (flightStatus == "Cancelled") {
            existingData->SetStatus("Cancelled");
        }
        else if (flightStatus == "Delayed") {
            if (existingData->GetStatus() == "Delayed") {
                existingData->SetSeatsDec();
            }
            else {
                printErrorCode(300); // 상태 변경 불가능
                return false;
            }
        }
        else {
            printErrorCode(300); // 잘못된 상태
            return false;
        }

        // 좌석이 0이 되면 AVL 트리에 추가
        if (existingData->GetNumberofSeats() == 0) {
            avl->Insert(existingData);
        }
    }

    return true;
}



bool Manager::PRINT_BP() {
    if (bp->getRoot() == nullptr) return false;
    bp->Print();
    return true;
}

bool Manager::SEARCH_BP(string name) {
    return bp->SearchModel(name);
}

bool Manager::SEARCH_BP(string start, string end) {
    return bp->SearchRange(start, end);
}

bool Manager::SEARCH_AVL(string name) {
    FlightData* result = avl->Search(name);

    ofstream fout("log.txt", ofstream::app);

    if (result == nullptr) {
        fout << "======== ERROR ========" << endl;
        fout << "500" << endl;
        fout << "=======================" << endl << endl;
        fout.close();
        return false;
    }

    fout << "====== SEARCH_AVL ======" << endl;
    fout << result->GetFlightNumber() << " | "
        << result->GetAirlineName() << " | "
        << result->GetDestination() << " | "
        << result->GetNumberofSeats() << " | "
        << result->GetStatus() << endl;
    fout << "========================" << endl << endl;

    fout.close();
    return true;
}

bool Manager::VPRINT(string type_) {
    if (Print_vector.empty()) return false;

    if (type_ == "A") {
        sort(Print_vector.begin(), Print_vector.end(), [](FlightData* a, FlightData* b) {
            if (a->GetAirlineName() != b->GetAirlineName())
                return a->GetAirlineName() < b->GetAirlineName();
            if (a->GetDestination() != b->GetDestination())
                return a->GetDestination() < b->GetDestination();
            return a->GetStatus() > b->GetStatus();
            });
    }
    else if (type_ == "B") {
        sort(Print_vector.begin(), Print_vector.end(), [](FlightData* a, FlightData* b) {
            if (a->GetDestination() != b->GetDestination())
                return a->GetDestination() < b->GetDestination();
            if (a->GetStatus() != b->GetStatus())
                return a->GetStatus() < b->GetStatus();
            return a->GetAirlineName() > b->GetAirlineName();
            });
    }
    else {
        return false;
    }

    ofstream fout("log.txt", ofstream::app);
    fout << "======= VPRINT =======" << endl;
    for (auto flight : Print_vector) {
        fout << flight->GetAirlineName() << " | "
            << flight->GetFlightNumber() << " | "
            << flight->GetDestination() << " | "
            << flight->GetStatus() << endl;
    }
    fout << "=======================" << endl;
    fout.close();

    return true;
}

void Manager::PrintSuccess(string cmd) {
    ofstream fout;
    fout.open("log.txt", ios::app);
    fout << "========== " << cmd << " ==========" << endl;
    fout << "Success" << endl;
    fout << "=========================" << endl << endl;
    fout.close();
}

void Manager::printErrorCode(int n) {
    ofstream fout;
    fout.open("log.txt", ios::app);
    fout << "========== ERROR ==========" << endl;
    fout << n << endl;
    fout << "===========================" << endl << endl;
    fout.close();
}