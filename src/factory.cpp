#include "factory.hpp"


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
    bool consistant=true;

    std::for_each(Ramps.begin(),Ramps.end(),[&consistant](Ramp &ramp)
    {
        auto prefs=ramp.receiver_preferences_.get_preferences();
        if(prefs.empty()){consistant=false;}
    } );

    std::for_each(Workers.begin(),Workers.end(),[this,&consistant](Worker &worker)
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
            }});

        auto wprefs=worker.receiver_preferences_.get_preferences();
        auto wid=worker.get_id();
        bool anothercheck=false;
        for(auto it=wprefs.begin(); it!=wprefs.end();it++)
        {
            auto type=it->first->get_receiver_type();

            if(it->first->get_id()!=wid || type==STOREHOUSE)
            {
                anothercheck=true;
            }
        }

        if(!atleastone){consistant=false;}
        if(!anothercheck){consistant=false;}
    });

    std::for_each(Storehouses.begin(),Storehouses.end(),[this,&consistant](Storehouse &storehouse)
    {
        auto id=storehouse.get_id();
        bool atleastone=false;
        std::for_each(Workers.begin(),Workers.end(),[id,&atleastone](Worker &worker)
        {
            auto prefs=worker.receiver_preferences_.get_preferences();
            for(auto it=prefs.begin(); it!=prefs.end();it++)
            {
                if(it->first->get_id()==id)
                {
                    atleastone = true;
                }
            }
        } );

        if(!atleastone){consistant=false;}
    });

    return consistant;
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
