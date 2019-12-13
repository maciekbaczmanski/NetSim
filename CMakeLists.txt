cmake_minimum_required(VERSION 3.12)
project(NetSim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(
        include
        src
)

add_executable(NetSim main.cpp src/package.cpp include/package.hpp src/storage_types.cpp include/storage_types.hpp include/types.hpp)
# == Unit testing using Google Testing Framework ==

