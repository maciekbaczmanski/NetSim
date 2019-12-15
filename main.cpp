#include <iostream>
#include "package.hpp"
#include "storage_types.hpp"
int main(){
    /**
    Package* p1 = new Package();
    Package* p2 = new Package();


    std::cout<< p1->get_id() <<std::endl;
    std::cout<< p2->get_id() <<std::endl;
    delete p1;
    delete p2;
    Package* p3 = new Package();
    std::cout<< p3->get_id() <<std::endl;
    */

    PackageQueue PQ(PackageQueueType::FIFO);
    PQ.push(Package());
    PQ.push(Package());
    PQ.push(Package());


    std::cout<< "Done" <<std::endl;

return 0;
}
