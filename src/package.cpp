#include "package.hpp"

std::deque<ElementID> Package::used_IDs;

Package::Package() {
    this->assign_ID();
}

Package::~Package() {
    std::deque<ElementID>::iterator iter = find(used_IDs.begin(),used_IDs.end(),ID);

    if(iter != used_IDs.end()){
        used_IDs.erase(iter);
    }
}

bool Package::is_ID_used(const ElementID &newID){
    return find(used_IDs.begin(), used_IDs.end(), newID) != used_IDs.end();
}

void Package::assign_ID(){
    ElementID newID = 1;
    while(is_ID_used(newID)){
        newID = newID + 1;
    }
    ID = newID;
    used_IDs.push_back(ID);
}


