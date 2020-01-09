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
    PackageQueueType wqt2=PackageQueueType ::LIFO;
    PackageQueueType wqt3=PackageQueueType ::LIFO;
    PackageQueueType sqt=PackageQueueType ::LIFO;

    Ramp r1(1, 5);
    Worker w1(1,3,std::make_unique<PackageQueue>(wqt));
    Worker w2(2,1,std::make_unique<PackageQueue>(wqt2));
    Worker w3(3,3,std::make_unique<PackageQueue>(wqt3));
    Storehouse s1(4,std::make_unique<PackageQueue>(sqt));

    r1.receiver_preferences_.add_receiver(&w1);
    w1.receiver_preferences_.add_receiver(&s1);
    r1.receiver_preferences_.add_receiver(&w2);
    r1.receiver_preferences_.add_receiver(&w3);

    w2.receiver_preferences_.add_receiver(&s1);
    w3.receiver_preferences_.add_receiver(&s1);

    std::optional<Package> z;
    for(double i=1;i<15;i++)
    {
        std::cout<<"\nTour nmb: "<<i<<"\n";

        r1.deliver_goods(i);

        r1.send_package();
        w1.send_package();
        w2.send_package();

        w1.do_work(i);
        w2.do_work(i);



    }
//
//    std::cout<< PQ.size() <<std::endl;
//    std::cout<< PQ.empty() <<std::endl;

    std::cout<< "Done\n\n" <<std::endl;
    
    


return 0;
}
