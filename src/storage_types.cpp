#include "storage_types.hpp"

Package PackageQueue::pop() {

    switch(queueType){
        case PackageQueueType::FIFO:{
            Package returnedPackage = std::move(queue.front());
            queue.pop_front();
            return returnedPackage;
            break;
        }

        case PackageQueueType ::LIFO:{
            Package returnedPackage = std::move(queue.back());
            queue.pop_back();
            return returnedPackage;
            break;
        }
    }
    return Package();
}
