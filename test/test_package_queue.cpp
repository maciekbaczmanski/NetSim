#include "gtest/gtest.h"

#include "storage_types.hpp"
/* TODO:
class PackageSender:
    wysyłanie półproduktu: czy po wysłaniu bufor jest pusty?


class ReceiverPreferences
    dodawanie/usuwanie odbiorcy: skalowanie prawdopodobieństwa

    wybór odbiorcy: czy odpowiedni wybrany, gdy damy “zmockowany” generator liczb losowych?


class Ramp
    dostawa: czy dostawa odbywa się we właściwej turze? czy półprodukt trafia od razu do bufora?


class Worker
    odbiór półproduktu: czy poprawnie wstawiony do kolejki?

    wykonywanie pracy: czy robotnik przetwarza półprodukt odpowiednią liczbę tur? czy przekazuje dalej odpowiedni półprodukt?


class Storehouse
    odbiór półproduktu: czy poprawnie wstawiony do magazynu?
 */
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