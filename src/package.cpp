#include "package.hpp"

std::set<ElementID> Package::used_IDs;
std::set<ElementID> Package::free_IDs;
Package::Package() {
    this->assign_ID();
    //used_IDs.emplace(ID);
}

Package::~Package() {
    /**std::set<ElementID>::iterator iter = find(used_IDs.begin(),used_IDs.end(),ID);

    if(iter != used_IDs.end()){
       // used_IDs.erase(iter);
    }
     */
    if(via_rvalue == false){
        used_IDs.erase(ID);
        free_IDs.emplace(ID);
    }

}

Package::Package(Package &&other) {
    ID = std::move(other.ID);
    other.via_rvalue = true;
}


bool Package::is_ID_used(const ElementID &newID){
    return used_IDs.find(newID) != used_IDs.end();
    //return find(used_IDs.begin(), used_IDs.end(), newID) != used_IDs.end();
}

void Package::assign_ID(){
    ElementID newID = 1;
    /**
    while(is_ID_used(newID)){
        newID = newID + 1;
    }
    */
    if(is_ID_used(newID)){
        newID = *free_IDs.begin();
    }

    ID = newID;
    used_IDs.emplace(ID);
    free_IDs.erase(ID);
    free_IDs.emplace(ID+1);
}









