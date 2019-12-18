#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include "package.hpp"

enum class PackageQueueType{
    LIFO,
    FIFO
};

class IPackageStockpile{
public:
    using packageIt = std::deque<Package>::const_iterator;
    virtual void push(Package&& pack)= 0;
    virtual bool empty() = 0;
    virtual size_type size() = 0;
    virtual packageIt begin() = 0;
    virtual const packageIt cbegin() = 0;
    virtual packageIt end()= 0;
    virtual const packageIt cend() = 0;



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
    PackageQueue(PackageQueueType type){ queueType = type; };
    void push(Package&& pack){ queue.emplace_back(std::move(pack)); };
    bool empty(){ return queue.empty(); };
    size_type size() { return size_type(queue.size()); };
    Package pop();
    PackageQueueType get_queue_type(){ return queueType; };
    packageIt begin() { return queue.begin(); };
    const packageIt cbegin() { return queue.cbegin(); };
    packageIt end() { return queue.end(); };
    const packageIt cend() { return queue.cend(); };

};
#endif //NETSIM_STORAGE_TYPES_HPP
