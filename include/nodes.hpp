#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP
//TODO:  classes: IPackageReceiver, Storehouse, ReceiverPreferences, PackageSender, Ramp i Worker

/*
IPackageReceiver <interface> (Worker, Storehouse):
    receive_package(p: Package&&) : void
    get_id(void) : ElementID {query}

Storehouse (IPackageStockpile):
    Storehouse(id: ElementID, d: std::unique_ptr<IPackageStockpile>)

ReceiverPreferences (PackageSender):
    add_receiver(r: IPackageReceiver*) : void
    remove_receiver(r: IPackageReceiver*) : void
    choose_receiver(void) : IPackageReceiver*

PackageSender (Ramp, Worker):
    receiver_preferences_: ReceiverPreferences

    send_package(void) : void
    get_sending_buffer(void) : std::optional<Package> {query}
    push_package(Package&&) : void  {PROTECTED}

Ramp ():
    Ramp(id: ElementID, di: TimeOffset) : void
    deliver_goods(t: Time) : void
    get_delivery_interval(void) : TimeOffset {query}
    get_id(void) : ElementID {query}

Worker ():
    Worker(id: ElementID, pd: TimeOffset, q: std::unique_ptr<PackageQueue>) : void
    do_work(t: Time) : void
    get_processing_duration(void) : TimeOffset {query}
    get_package_processing_start_time(void) : Time {query}

*/
#endif //NETSIM_NODES_HPP
