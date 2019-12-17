#include "gtest/gtest.h"

#include "storage_types.hpp"

TEST(PackageTest, IDassignmentManual){

    Package* p1 = new Package();
    Package* p2 = new Package();

    ASSERT_EQ(p1->get_id(),1);
    ASSERT_EQ(p2->get_id(),2);

    delete p1;

    Package* p3 = new Package();

    ASSERT_EQ(p3->get_id(),1);

    delete p2;
    delete p3;
}

TEST(PackageQueueTest, PopQueueFIFO){
    PackageQueue PQ_FIFO(PackageQueueType::FIFO);
    PQ_FIFO.push(Package());
    PQ_FIFO.push(Package());
    PQ_FIFO.push(Package());

    Package temp = PQ_FIFO.pop();
    Package temp2 = PQ_FIFO.pop();

    ASSERT_EQ(temp.get_id(),1);
    ASSERT_EQ(temp2.get_id(),2);
}

TEST(PackageQueueTest, PopQueueLIFO){
    PackageQueue PQ_LIFO(PackageQueueType::LIFO);
    PQ_LIFO.push(Package());
    PQ_LIFO.push(Package());
    PQ_LIFO.push(Package());

    Package temp = PQ_LIFO.pop();
    Package temp2 = PQ_LIFO.pop();

    ASSERT_EQ(temp.get_id(),3);
    ASSERT_EQ(temp2.get_id(),2);
}