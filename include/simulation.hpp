#include "factory.hpp"
#include "nodes.hpp"
#include "types.hpp"

#ifndef NETSIM_SIMULATION_HPP
#define NETSIM_SIMULATION_HPP

void simulate(Factory  &factory, TimeOffset d,std::function<void(Factory&,Time)> func);


#endif //NETSIM_SIMULATION_HPP
