#include "nodes.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver *r)
{
    double preference=1;
    double newsum=0.0;
    mapofreceivers[r]=preference;
    for (auto &pair : mapofreceivers)
    {
        mapofreceivers[pair.first]=1.0/mapofreceivers.size();
        newsum=newsum+pair.second;
    }
    if(newsum!=1.0)
    {
        mapofreceivers[r]=mapofreceivers[r]+1.0-newsum;
    }
}


void ReceiverPreferences::remove_receiver(IPackageReceiver *r)
{
    IPackageReceiver* memory=r;
    double newsum=0.0;
    mapofreceivers.erase(r);
    for (const auto &pair : mapofreceivers)
    {
        mapofreceivers[pair.first]=1.0/mapofreceivers.size();
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
    IPackageReceiver* remember=mapofreceivers.rbegin()->first;
    std::map<IPackageReceiver*, double>::reverse_iterator it;
    for(it=mapofreceivers.rbegin();it!=mapofreceivers.rend();++it)
    {
        distribution=distribution+it->second;
        remember=it->first;
        if(randnmb<distribution)
        {
            break;
        }
    }
    return remember;
}

void PackageSender::push_package(Package &&package)
{
    bucket=std::move(package);
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
Ramp::Ramp(ElementID id, TimeOffset di)
{
    id_=id;
    di_=di;
}

TimeOffset Ramp::get_delivery_interval()
{
    return di_;
}

 ElementID Ramp::get_id()
{
    return  id_;
}

void Ramp::deliver_goods(Time t)
{
    if(t%di_==1)
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
    processing=std::nullopt;

}

void Worker::do_work(Time t)
{

    if(!queue->empty() && !processing)
    {
        processing=queue->pop();
        starttime=t;
    }

    if (t-starttime==pd_-1  && processing)
    {
        push_package(std::move(*processing));
        processing.reset();
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
    std::cout<<"\nStoregouse id: "<<get_id()<<" Package id: "<<p.get_id();
    d_->push(std::move(p));

}

void Worker:: receive_package(Package &&p)
{
    std::cout<<"\nWorker id: "<<get_id()<<" Package id: "<<p.get_id();
    queue->push(std::move(p));
}