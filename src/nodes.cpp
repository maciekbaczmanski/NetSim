#include "nodes.hpp"

//TODO: funkcjonalnosci klas z nodes.hpp




void ReceiverPreferences::add_receiver(IPackageReceiver *r, double preference=1)
{
    double sum=0.0;
    double newsum=0.0;
    mapofreceivers[r]=preference;
    for (const auto &pair : mapofreceivers)
    {
        sum=sum+pair.second;
    }
    for (auto &pair : mapofreceivers)
    {
        mapofreceivers[pair.first]=mapofreceivers[pair.first]/sum;
        newsum=newsum+pair.second;
    }
    if(newsum!=1.0)
    {
        mapofreceivers[r]=mapofreceivers[r]+1.0-newsum;
    }
}


void ReceiverPreferences::remove_receiver(IPackageReceiver *r)
{
    double sum=0.0;
    IPackageReceiver* memory=r;
    double newsum=0.0;
    mapofreceivers.erase(r);
    for (const auto &pair : mapofreceivers)
    {
        sum=sum+pair.second;
    }
    for (const auto &pair : mapofreceivers)
    {
        mapofreceivers[pair.first]=mapofreceivers[pair.first]/sum;
        newsum=newsum+pair.second;
        memory=pair.first;
    }
    if(newsum!=1.0)
    {
        mapofreceivers[memory]=mapofreceivers[memory]+1.0-newsum;
    }
}


IPackageReceiver* ReceiverPreferences::choose_receiver()
{
    double randnmb=generator_();
    double distribution=0.0;
    for (const auto &pair: mapofreceivers)
    {
        distribution=distribution+pair.second;
        if(randnmb<distribution)
            return pair.first;
        if (randnmb==1.0 and distribution==1.0)
            return pair.first;
    }
}

void PackageSender::push_package(Package &&package)
{
    // FIXME: sprawdzić czy to w ogóle ma prawo działać
    bucket.emplace(std::move(package));
}

std::optional<Package> PackageSender::get_sending_buffer()
{
    std::optional<Package> returnbucket=std::move(bucket);
    bucket.reset();
    return returnbucket;
}





















/*
class IPackageReceiver
{
public:
    void receive_package(Package&& p);
    ElementID get_id();
};

class Storehouse
{
public:
    Storehouse(std::unique_ptr<IPackageStockpile> d, ElementID id);
};

class ReceiverPreferences
{
public:
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
};

class PackageSender
{
public:
    void send_package();
    std::optional<Package> get_sending_buffer();
    ReceiverPreferences receiver_preferences_;

protected:
    void push_package(Package&&);
};

class Ramp : public PackageSender
{
public:
    Ramp(ElementID id, TimeOffset di);
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval();
    ElementID get_id();
};

class Worker : public PackageSender
{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> q);
    void do_work(Time t);
    TimeOffset get_processing_duration();
    Time get_package_processing_start_time();
};





 */