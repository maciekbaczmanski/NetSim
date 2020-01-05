#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP
#include "helpers.hpp"
#include "storage_types.hpp"
#include <iostream>
#include <optional>
#include <memory>
#include <map>
#include <functional>
class IPackageReceiver
{
public:
    virtual void receive_package(Package&& p)= 0;
    virtual ElementID get_id() = 0;
};

class Storehouse: public IPackageReceiver
{
public:
    Storehouse(ElementID id,std::unique_ptr<IPackageStockpile> d): d_(std::move(d)), id_(id) {}
    ElementID get_id();
    void receive_package(Package && p);
private:
    std::unique_ptr<IPackageStockpile> d_;
    ElementID id_;
};

class ReceiverPreferences
{

public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    using reverse_iterator = preferences_t ::reverse_iterator;
    ReceiverPreferences(ProbabilityGenerator  generator_function=r_generator): generator_(generator_function){}
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const_iterator begin() {return mapofreceivers.begin();}
    const const_iterator cbegin() {return mapofreceivers.cbegin();}
    const_iterator end() {return mapofreceivers.end();}
    const const_iterator cend() {return mapofreceivers.cend();}
    reverse_iterator rbegin() {return mapofreceivers.rbegin();}
    reverse_iterator rend() {return mapofreceivers.rend();}

private:
    preferences_t mapofreceivers;
    ProbabilityGenerator generator_;
};

class PackageSender
{
public:
    void send_package();
    std::optional<Package> get_sending_buffer();
    bool buffer_empty();
    ReceiverPreferences receiver_preferences_;
protected:
    void push_package(Package&& package);

private:
    std::optional<Package> bucket;
};

class Ramp : public PackageSender
{
public:
    Ramp(ElementID id, TimeOffset di);
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval();
    ElementID get_id();

private:
    ElementID id_;
    TimeOffset di_;
};

class Worker : public PackageSender, public IPackageReceiver
{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> q);
    void do_work(Time t);
    void receive_package(Package && p);
    TimeOffset get_processing_duration();
    Time get_package_processing_start_time();
    ElementID get_id();


private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<PackageQueue> queue;
    Time starttime;
    std::optional<Package> processing;
};




#endif //NETSIM_NODES_HPP
