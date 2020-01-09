#include "helpers.hpp"

std::random_device rd;
std::mt19937 rng(rd());


double default_probability_generator() {
    double rand = std::generate_canonical<double, 10>(rng);
    return rand;
}

//double r_generator()
//{
//    return 0.0;
//}


std::function<double()> probability_generator = default_probability_generator;
