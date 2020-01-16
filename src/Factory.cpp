
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

    std::map<PackageSender*, node_color > color;
    ////MARK EVERY SENDER (RAMPS, WORKERS) AS NOT VISITED
    std::for_each(Ramps.begin(),Ramps.end(),[&color](auto &sender){
        color.emplace(std::make_pair(&sender,node_color::NOT_VISITED)); });

    std::for_each(Workers.begin(),Workers.end(),[&color](auto &sender){
        color.emplace(std::make_pair(&sender,node_color::NOT_VISITED)); });

    std::for_each(Ramps.begin(),Ramps.end(),[this](auto &ramp){
        try{
            if(sender_has_reachable_storehouse(&ramp)){
                return true;
            }

        }catch (no_reachable_storehouse_error &e){
            return false;
        }
        return false;
    });

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

    for(auto it = Ramps.begin();it!=Ramps.end();it++){
        auto ramp_prefs =
    }

    Workers.remove_by_id(id);
}

void Factory::remove_storehouse(ElementID id) {


    Storehouses.remove_by_id(id);
}
