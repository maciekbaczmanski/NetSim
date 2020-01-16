cmake_minimum_required(VERSION 3.12)
project(NetSim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wno-deprecated-declarations)

include_directories(
        include)

set(SOURCE_FILES
        src/package.cpp
        src/nodes.cpp
        src/storage_types.cpp
        src/helpers.cpp
        src/Factory.cpp include/Factory.hpp)

add_executable(NetSim ${SOURCE_FILES} main.cpp)

# == Unit testing using Google Testing Framework ==

set(SOURCES_FILES_TESTS
        finaltest/test_Factory.cpp
        #finaltest/test_factory_io.cpp
        #finaltest/test_nodes.cpp
        #finaltest/test_package.cpp
        #finaltest/test_package_queue.cpp
        #finaltest/test_simulate.cpp
        #finaltest/test_storage_types.cpp src/Factory.cpp include/Factory.hpp
        )


add_executable(NetSim__test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} finaltest/main_gtest.cpp)
target_compile_definitions(NetSim__test PUBLIC EXERCISE_ID=EXERCISE_ID_FACTORY)

target_include_directories(NetSim__test PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        )
target_link_libraries(NetSim__test gmock)


add_subdirectory(googletest-master googletest-master)




