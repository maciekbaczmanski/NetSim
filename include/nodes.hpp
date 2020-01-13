#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP
#include "helpers.hpp"
#include "storage_types.hpp"
#include <iostream>
#include <optional>
#include <memory>
#include <map>
#include <functional>


enum ReceiverType {WORKER,
    STOREHOUSE};

class IPackageReceiver
{
public:
    virtual void receive_package(Package&& p)= 0;
    virtual ReceiverType get_receiver_type() = 0;
    virtual ElementID get_id() const = 0;
};

class Storehouse: public IPackageReceiver
{
public:
    Storehouse(ElementID id,std::unique_ptr<IPackageStockpile> d= std::make_unique<PackageQueue>(PackageQueueType::LIFO)): d_(std::move(d)), id_(id) {}
    ElementID get_id() const;
    void receive_package(Package && p);
    ReceiverType get_receiver_type(){ return ReceiverType::STOREHOUSE; };
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
    ReceiverPreferences(ProbabilityGenerator  generator_function=probability_generator): generator_(generator_function){}
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const_iterator begin() const {return preferences_.cbegin();}
    const_iterator cbegin() const {return preferences_.cbegin();}
    const_iterator end() const {return preferences_.cend();}
    const_iterator cend() const {return preferences_.cend();}
    reverse_iterator rbegin() {return preferences_.rbegin();}
    reverse_iterator rend() {return preferences_.rend();}
    const preferences_t& get_preferences() const { return preferences_; }

private:
    preferences_t preferences_;
    ProbabilityGenerator generator_;
};

class PackageSender
{
public:
    //PackageSender(PackageSender&&)=default;
    void send_package();
    std::optional<Package> & get_sending_buffer();
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
    ElementID get_id() const;

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
    ReceiverType get_receiver_type(){ return ReceiverType::WORKER; };
    TimeOffset get_processing_duration();
    Time get_package_processing_start_time();
    ElementID get_id() const;


private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<PackageQueue> queue;
    Time starttime;
    std::optional<Package> processing;
};




#endif //NETSIM_NODES_HPP
