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

Package::Package(Package &&other) {
    other.get_id();
}

Package &Package::operator=(Package &&other) {
    other.get_id();
    return *this;
}

bool Package::is_ID_used(const ElementID &newID){
    for(const auto& id: used_IDs){
        if(newID == id){
            return true;
        }
    }
    return false;
}

void Package::assign_ID(){
    ElementID newID = 1;
    while(is_ID_used(newID)){
        newID = newID + 1;
    }
    ID = newID;
    used_IDs.push_back(ID);
}


