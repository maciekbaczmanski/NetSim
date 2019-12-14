#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include "package.hpp"

enum class PackageQueueType{
    LIFO,
    FIFO
};

class IPackageStockpile{
public:
    virtual void push(Package&&) = 0;
    virtual bool empty() = 0;
    virtual size_type size() = 0;
    using package_it = std::deque<Package>::const_iterator;

protected:
    std::deque<Package> queue;
    PackageQueueType queueType;
};

class IPackageQueue: public IPackageStockpile{
public:
    virtual Package pop() =0;
    virtual PackageQueueType get_queue_type() = 0;
};

class PackageQueue: public IPackageQueue{
public:

//PackageQueue(PackageQueueType type): queueType(type){};
//error: class 'PackageQueue' does not have any field named 'queueType'
// WHY THO? dziedzicze go z IPackageStockpile
};
#endif //NETSIM_STORAGE_TYPES_HPP
