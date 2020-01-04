#include "nodes.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver *r)
{
    double preference=1;
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
    IPackageReceiver* remember;
    for (const auto &pair: mapofreceivers)
    {
        distribution=distribution+pair.second;
        remember=pair.first;
        if(randnmb<distribution)
        {
            return pair.first;
        }

    }
    return remember;
}

void PackageSender::push_package(Package &&package)
{
    bucket.emplace(std::move(package));
}

std::optional<Package> PackageSender::get_sending_buffer()
{
    if(bucket) return std::move(bucket);
    else return std::nullopt;
}

bool PackageSender::buffer_empty()
{
    if(bucket) return true;
    else return false;
}
void PackageSender::send_package()
{

    if(bucket)
    {
        IPackageReceiver* receiver =receiver_preferences_.choose_receiver();
        receiver->receive_package(std::move(*bucket));
        bucket.reset();

    }


}

TimeOffset Ramp::get_delivery_interval()
{
    return di_;
}

ElementID Ramp::get_id()
{
    return id_;
}

void Ramp::deliver_goods(Time t)
{

    if(t%di_==0)
    {
        Package p;
        push_package(std::move(p));

    }
}

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> q)
{
    id_=id;
    pd_=pd;
    queue=std::move(q);
    starttime=0;
}

void Worker::do_work(Time t)
{
    if (t-starttime==pd_ )
    {

        send_package();
    }

    if(!queue->empty() && !buffer_empty())
    {

        push_package(queue->pop());
        starttime=t;

    }

}

TimeOffset Worker::get_processing_duration()
{
    return pd_;
}

Time Worker::get_package_processing_start_time()
{
    return starttime;
}

ElementID Worker::get_id()
{
    return id_;
}
ElementID Storehouse::get_id()
{
    return id_;
}

void Storehouse:: receive_package(Package &&p)
{

    std::cout<<"received pack: "<<p.get_id()<<" storehouse id: "<<get_id()<<"\n";
    d_->push(std::move(p));
}

void Worker:: receive_package(Package &&p)
{
    std::cout<<"received pack: "<<p.get_id()<<" worker id: "<<get_id()<<"\n";

    queue->push(std::move(p));
}