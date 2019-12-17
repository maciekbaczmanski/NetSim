cmake_minimum_required(VERSION 3.12)
project(NetSim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wno-deprecated-declarations)

include_directories(
        include)

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        )

add_executable(NetSim ${SOURCE_FILES} main.cpp)

# == Unit testing using Google Testing Framework ==

set(SOURCES_FILES_TESTS
        test/test_package_queue.cpp)

add_executable(NetSim__test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)

target_include_directories(NetSim__test PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        )

add_subdirectory(googletest-master googletest-master)

target_link_libraries(NetSim__test gmock)


