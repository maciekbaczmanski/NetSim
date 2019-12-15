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
    Package(Package&& other);
    Package& operator = (Package&& other) = default;
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
