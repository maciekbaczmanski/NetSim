
#include <Factory.hpp>

#include "Factory.hpp"

enum node_color{NOT_VISITED,VISITED,VERIFIED};

struct no_reachable_storehouse_error : public std::exception
{
    /**
    Exception thrown if no reachable storehouse
     was found for a given node
    */
    const char * what () const throw (){
        return "No reachable storehouse";
    }
};

bool Factory::is_consistent() {
    if(Ramps.begin()==Ramps.end()){return false;}
    if(Workers.begin()==Workers.end()){return false;}
    if(Storehouses.begin()==Storehouses.end()){return false;}

    std::for_each(Ramps.begin(),Ramps.end(),[](Ramp &ramp)
    {
       auto prefs=ramp.receiver_preferences_.get_preferences();
       if(prefs.empty()){return false;}
    } );

    std::for_each(Workers.begin(),Workers.end(),[this](Worker &worker)
    {
        auto id=worker.get_id();
        bool atleastone=false;
        std::for_each(Ramps.begin(),Ramps.end(),[id,&atleastone](Ramp &ramp)
        {
            auto prefs=ramp.receiver_preferences_.get_preferences();
            for(auto it=prefs.begin(); it!=prefs.end();it++)
            {
                if(it->first->get_id()==id)
                {
                    atleastone = true;
                }
            }
        } );

        std::for_each(Workers.begin(),Workers.end(),[id,&atleastone](Worker &worker) {
            if(worker.get_id()!=id) {
                auto prefs = worker.receiver_preferences_.get_preferences();
                for (auto it = prefs.begin(); it != prefs.end(); it++) {
                    if (it->first->get_id() == id) {
                        atleastone = true;
                    }
                }
            }


            if(!atleastone){return false;}
        });













//    std::map<PackageSender*, node_color > color;
//    ////MARK EVERY SENDER (RAMPS, WORKERS) AS NOT VISITED
//    std::for_each(Ramps.begin(),Ramps.end(),[&color](auto &sender){
//        color.emplace(std::make_pair(&sender,node_color::NOT_VISITED)); });
//
//    std::for_each(Workers.begin(),Workers.end(),[&color](auto &sender){
//        color.emplace(std::make_pair(&sender,node_color::NOT_VISITED)); });
//
//    std::for_each(Ramps.begin(),Ramps.end(),[this](auto &ramp){
//        try{
//            if(sender_has_reachable_storehouse(&ramp)){
//                return true;
//            }
//
//        }catch (no_reachable_storehouse_error &e){
//            return false;
//        }
//        return false;
//    });


    return false;
}

bool Factory::sender_has_reachable_storehouse(PackageSender* node){
    ////TEMP
    node = node;
    return false;
}

void Factory::do_deliveries(Time time) {
    std::for_each(Ramps.begin(),Ramps.end(),[time](Ramp &ramp){ ramp.deliver_goods(time);} );
}

void Factory::do_package_passing() {
    std::for_each(Ramps.begin(),Ramps.end(),[](Ramp &ramp){ ramp.send_package(); } );
    std::for_each(Workers.begin(),Workers.end(),[](Worker &worker){ worker.send_package(); });
}

void Factory::do_work(Time time) {
    std::for_each(Workers.begin(),Workers.end(),[time](Worker &worker){ worker.do_work(time); });
}

void Factory::remove_worker(ElementID id) {

    std::for_each(Ramps.begin(),Ramps.end(),[id](Ramp &ramp)
    {
    auto prefs=ramp.receiver_preferences_.get_preferences();
        for(auto it=prefs.begin(); it!=prefs.end();it++)
        {
            if(it->first->get_id()==id)
            {
                ramp.receiver_preferences_.remove_receiver(it->first);
            }
        }
    } );


    Workers.remove_by_id(id);
}

void Factory::remove_storehouse(ElementID id) {


    std::for_each(Workers.begin(),Workers.end(),[id](Worker &worker)
    {
        auto prefs=worker.receiver_preferences_.get_preferences();
        for(auto it=prefs.begin(); it!=prefs.end();it++)
        {
            if(it->first->get_id()==id)
            {
                worker.receiver_preferences_.remove_receiver(it->first);
            }
        }
    } );

    Storehouses.remove_by_id(id);
}
