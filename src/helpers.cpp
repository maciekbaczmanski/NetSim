#include "helpers.hpp"

double r_generator() {
    std::random_device rd;
    std::mt19937 rng(rd());
    return std::generate_canonical<double, 1>(rng);
}