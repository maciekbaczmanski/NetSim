#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include <deque>
#include <set>
#include <algorithm>
#include "types.hpp"

class Package{
public:
    Package();
    ~Package();
    Package(Package&& other){
        //used_IDs = std::move(other.used_IDs);
        //free_IDs = std::move(other.free_IDs);
        ID = std::move(other.ID);
        other.via_rvalue = true;
    };
    Package& operator = (Package&&) = default;
    ElementID get_id() const { return ID; };
private:
    ElementID ID;
    static std::set<ElementID> used_IDs;
    static std::set<ElementID> free_IDs;
    bool is_ID_used(const ElementID &newID);
    void assign_ID();
    bool via_rvalue = false;
};

#endif //NETSIM_PACKAGE_HPP
