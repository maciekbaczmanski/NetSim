#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include "package.hpp"
#include <deque>
#include <list>

enum class PackageQueueType{
    LIFO,
    FIFO
};

class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;
    virtual void push(Package&& pack)= 0;
    virtual bool empty() = 0;
    virtual size_type size() = 0;
    virtual  const_iterator begin() const= 0;
    virtual  const_iterator cbegin()const = 0;
    virtual  const_iterator end()const= 0;
    virtual  const_iterator cend() const= 0;



protected:
    std::list<Package> queue;
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
    const_iterator begin() const{ return queue.cbegin(); };
    const_iterator cbegin() const{ return queue.cbegin(); };
    const_iterator end() const{ return queue.cend(); };
    const_iterator cend() const { return queue.cend(); };

};
#endif //NETSIM_STORAGE_TYPES_HPP
