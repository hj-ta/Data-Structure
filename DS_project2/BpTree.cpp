#include "BpTree.h"
using namespace std;

bool BpTree::Insert(FlightData* newData) {
    string key = newData->GetFlightNumber();

    // B+ Tree가 비어있는 경우 새 루트 생성
    if (root == nullptr) {
        root = new BpTreeDataNode();
        ((BpTreeDataNode*)root)->insertDataMap(key, newData);
        return true;
    }

    // 삽입 위치 탐색
    BpTreeNode* targetNode = searchDataNode(key);

    // 기존 데이터 존재 여부 확인
    auto dataMap = ((BpTreeDataNode*)targetNode)->getDataMap();
    if (dataMap->find(key) != dataMap->end()) {
        FlightData* existingData = dataMap->at(key);

        // 상태 정보 업데이트 가능
        string newStatus = newData->GetStatus();
        if (newStatus == "Boarding" || newStatus == "Delayed") {
            // 좌석 감소
            if (existingData->GetNumberofSeats() > 0) {
                existingData->SetSeatsDec();
            }
        }
        else if (newStatus == "Departure" || newStatus == "Cancelled") {
            // 좌석 수 감소 없음, 상태만 업데이트
            existingData->SetStatus(newStatus);
        }

        *fout << "Insert/Update: Flight status updated - " << key << endl;
        return true;
    }

    // 새 데이터를 삽입
    ((BpTreeDataNode*)targetNode)->insertDataMap(key, newData);

    // 노드가 초과된 경우 분할 처리
    if (excessDataNode(targetNode)) {
        splitDataNode(targetNode);
    }

    return true;
}


//////////////////
FlightData* BpTree::findFlightData(string flightNum) {
    // 데이터를 포함하는 DataNode를 검색
    BpTreeNode* targetNode = searchDataNode(flightNum);
    if (!targetNode) return nullptr;

    // 해당 DataNode에서 데이터를 검색
    auto dataMap = ((BpTreeDataNode*)targetNode)->getDataMap();
    auto it = dataMap->find(flightNum);
    
    // 데이터가 있으면 반환, 없으면 nullptr 반환
    return (it != dataMap->end()) ? it->second : nullptr;
}


// Check if a data node exceeds the order limit
bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
    auto dataNode = dynamic_cast<BpTreeDataNode*>(pDataNode);
    return dataNode->getDataMap()->size() > order - 1;
}

// Check if an index node exceeds the order limit
bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
    auto indexNode = dynamic_cast<BpTreeIndexNode*>(pIndexNode);
    return indexNode->getIndexMap()->size() > order - 1;
}

// Split a data node into two and update the parent index node
void BpTree::splitDataNode(BpTreeNode* pDataNode) {
    auto dataNode = dynamic_cast<BpTreeDataNode*>(pDataNode);
    auto dataMap = dataNode->getDataMap();

    // Determine split point
    int mid = dataMap->size() / 2;
    auto it = dataMap->begin();
    advance(it, mid);

    // Create new data node
    BpTreeDataNode* newNode = new BpTreeDataNode();
    for (auto iter = it; iter != dataMap->end(); ++iter) {
        newNode->insertDataMap(iter->first, iter->second);
    }
    dataMap->erase(it, dataMap->end());

    newNode->setNext(dataNode->getNext());
    if (newNode->getNext() != nullptr) {
        newNode->getNext()->setPrev(newNode);
    }
    newNode->setPrev(dataNode);
    dataNode->setNext(newNode);

    // Update parent index node
    if (dataNode->getParent() == nullptr) {
        BpTreeIndexNode* newRoot = new BpTreeIndexNode();
        newRoot->insertIndexMap(newNode->getDataMap()->begin()->first, newNode);
        newRoot->setMostLeftChild(dataNode);
        dataNode->setParent(newRoot);
        newNode->setParent(newRoot);
        root = newRoot;
    }
    else {
        BpTreeIndexNode* parent = dynamic_cast<BpTreeIndexNode*>(dataNode->getParent());
        parent->insertIndexMap(newNode->getDataMap()->begin()->first, newNode);

        if (excessIndexNode(parent)) {
            splitIndexNode(parent);
        }
    }
}

// Split an index node into two and update the parent index node
void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
    auto indexNode = dynamic_cast<BpTreeIndexNode*>(pIndexNode);
    auto indexMap = indexNode->getIndexMap();

    // Determine split point
    int mid = indexMap->size() / 2;
    auto it = indexMap->begin();
    advance(it, mid);

    // Create new index node
    BpTreeIndexNode* newNode = new BpTreeIndexNode();
    for (auto iter = next(it); iter != indexMap->end(); ++iter) {
        newNode->insertIndexMap(iter->first, iter->second);
    }
    indexMap->erase(next(it), indexMap->end());

    // Handle parent updates
    if (indexNode->getParent() == nullptr) {
        BpTreeIndexNode* newRoot = new BpTreeIndexNode();
        newRoot->insertIndexMap(newNode->getIndexMap()->begin()->first, newNode);
        newRoot->setMostLeftChild(indexNode);
        indexNode->setParent(newRoot);
        newNode->setParent(newRoot);
        root = newRoot;
    }
    else {
        BpTreeIndexNode* parent = dynamic_cast<BpTreeIndexNode*>(indexNode->getParent());
        parent->insertIndexMap(newNode->getIndexMap()->begin()->first, newNode);

        if (excessIndexNode(parent)) {
            splitIndexNode(parent);
        }
    }
}

// Find the data node that may contain the given key
BpTreeNode* BpTree::searchDataNode(string key) {
    BpTreeNode* currentNode = root;
    while (currentNode && dynamic_cast<BpTreeIndexNode*>(currentNode)) {
        auto indexNode = dynamic_cast<BpTreeIndexNode*>(currentNode);
        auto indexMap = indexNode->getIndexMap();
        auto it = indexMap->lower_bound(key);

        if (it == indexMap->end() || it->first > key) {
            currentNode = indexNode->getMostLeftChild();
        }
        else {
            currentNode = it->second;
        }
    }
    return currentNode;
}

// Search for a specific model name in the tree
bool BpTree::SearchModel(string model_name) {
    BpTreeNode* dataNode = searchDataNode(model_name);
    if (!dataNode) return false;

    auto dataMap = dynamic_cast<BpTreeDataNode*>(dataNode)->getDataMap();
    if (dataMap->find(model_name) != dataMap->end()) {
        FlightData* data = (*dataMap)[model_name];
        *fout << "========SEARCH_BP========" << endl;
        *fout << model_name << " | "
            << data->GetAirlineName() << " | "
            << data->GetDestination() << " | "
            << data->GetNumberofSeats() << " | "
            << data->GetStatus() << endl;
        *fout << "=========================" << endl;
        return true;
    }
    return false;
}

// Search for a range of keys in the tree
bool BpTree::SearchRange(string start, string end) {
    bool found = false;
    BpTreeNode* currentNode = root;

    // 가장 왼쪽 데이터 노드로 이동
    while (currentNode && dynamic_cast<BpTreeIndexNode*>(currentNode)) {
        currentNode = currentNode->getMostLeftChild();
    }

    // 데이터 노드 순회
    while (currentNode) {
        auto dataNode = dynamic_cast<BpTreeDataNode*>(currentNode);
        auto dataMap = dataNode->getDataMap();

        for (auto it = dataMap->begin(); it != dataMap->end(); ++it) {
            if (it->first >= start && it->first <= end) {
                FlightData* data = it->second;
                *fout << it->first << " | "
                    << data->GetAirlineName() << " | "
                    << data->GetDestination() << " | "
                    << data->GetNumberofSeats() << " | "
                    << data->GetStatus() << endl;
                found = true;
            }
        }

        currentNode = dataNode->getNext();
    }

    if (!found) {
        *fout << "========ERROR========" << endl;
        *fout << "400" << endl;
        *fout << "=====================" << endl;
    }
    return found;
}

// Print the entire B+ Tree
void BpTree::Print() {
    BpTreeNode* currentNode = root;
    while (currentNode && dynamic_cast<BpTreeIndexNode*>(currentNode)) {
        currentNode = currentNode->getMostLeftChild();
    }

    while (currentNode) {
        auto dataNode = dynamic_cast<BpTreeDataNode*>(currentNode);
        auto dataMap = dataNode->getDataMap();

        for (const auto& entry : *dataMap) {
            *fout << entry.first << " | "
                << entry.second->GetAirlineName() << " | "
                << entry.second->GetDestination() << " | "
                << entry.second->GetNumberofSeats() << " | "
                << entry.second->GetStatus() << endl;
        }

        currentNode = dataNode->getNext();
    }
}