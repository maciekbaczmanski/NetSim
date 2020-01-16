#ifndef NETSIM_TYPES_HPP
#define NETSIM_TYPES_HPP
#include <iostream>
#include <functional>

using ElementID = int;
using size_type = unsigned int;
using ProbabilityGenerator = std::function<double()>;
using TimeOffset=unsigned int;
using Time= unsigned int;

#endif //NETSIM_TYPES_HPP
