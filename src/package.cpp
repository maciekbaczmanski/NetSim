#include "package.hpp"

std::set<ElementID> Package::used_IDs;
std::set<ElementID> Package::free_IDs;

Package::Package() {
    this->assign_ID();
}

Package::~Package() {
    if(via_rvalue == false){
        used_IDs.erase(ID);
        free_IDs.emplace(ID);
    }
}

Package::Package(Package &&other) {
    ID = std::move(other.ID);
    other.via_rvalue = true;
}

Package &Package::operator=(Package &&other) {
    ID = other.ID;
    return *this;
}

bool Package::is_ID_used(const ElementID &newID){
    return used_IDs.find(newID) != used_IDs.end();
}

void Package::assign_ID(){
    ElementID newID = 1;

    if(is_ID_used(newID)){
        newID = *free_IDs.begin();
    }

    ID = newID;
    used_IDs.emplace(ID);
    free_IDs.erase(ID);
    free_IDs.emplace(ID+1);
}











