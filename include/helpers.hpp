#ifndef NETSIM_HELPERS_HPP
#define NETSIM_HELPERS_HPP
//TODO: ewentualne pomocnicze obiekty i funkcje globalne (np. generator liczb losowych) - plik ten może być pusty, ale musi się pojawić w rozwiązaniu zadania

#include <cstdlib>
#include <iostream>
#include <random>
#include <ctime>



double random_generator() {
    std::random_device rd;
    std::mt19937 rng(rd());
    return std::generate_canonical<double, 1>(rng);
}

#endif //NETSIM_HELPERS_HPP
