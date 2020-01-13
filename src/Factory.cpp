#include "Factory.hpp"

bool Factory::is_consistent() {
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
