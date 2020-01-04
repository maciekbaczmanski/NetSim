#include <iostream>

#include "storage_types.hpp"
#include "nodes.hpp"
int main(){

//    Package* p1 = new Package();
//    Package* p2 = new Package();
//
//
//    std::cout<< p1->get_id() <<std::endl;
//    std::cout<< p2->get_id() <<std::endl;
//    delete p1;
//    delete p2;
//    Package* p3 = new Package();
//    std::cout<< p3->get_id() <<std::endl;
//
//
//    PackageQueue PQ(PackageQueueType::LIFO);
    PackageQueueType wqt=PackageQueueType ::LIFO;
    PackageQueueType sqt=PackageQueueType ::LIFO;

    Ramp r1(1, 1);
    Worker w1(2,2,std::make_unique<PackageQueue>(wqt));
    Storehouse s1(3,std::make_unique<PackageQueue>(sqt));

    r1.receiver_preferences_.add_receiver(&w1);
    w1.receiver_preferences_.add_receiver(&s1);
std::cout<<"abc";
    std::optional<Package> z;
    for(double i=0;i<15;i++)
    {

        r1.deliver_goods(i);
        r1.send_package();
        w1.do_work(i);

//        z=w1.get_sending_buffer();
//        std::cout<<"NOW??\n\n";
//        if(z)
//        {
//            std::cout<<i<<"   "<<z.value().get_id()<<"\n";
//        }

    }
//
//    std::cout<< PQ.size() <<std::endl;
//    std::cout<< PQ.empty() <<std::endl;

    std::cout<< "Done" <<std::endl;


return 0;
}
