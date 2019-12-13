#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include <deque>
#include <algorithm>
#include "types.hpp"

class Package{
public:
    Package();
    ~Package();
    Package(Package&& other);
    Package& operator = (Package&& other);
    ElementID get_id() const { return ID; };
private:
    ElementID ID;
    static std::deque<ElementID> used_IDs;
    bool is_ID_used(const ElementID &newID);
    void assign_ID();
};

#endif //NETSIM_PACKAGE_HPP
