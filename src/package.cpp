#include "package.hpp"

std::deque<ElementID> Package::used_IDs;

Package::Package() {

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
}
