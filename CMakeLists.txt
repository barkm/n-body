cmake_minimum_required(VERSION 3.6)
project(n_body)

set(CMAKE_CXX_STANDARD 11)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

set(CMAKE_CXX_COMPILER mpicxx)

set(SOURCE_FILES
        misc/body.cpp
        misc/body.h
        misc/gen_bodies.cpp
        misc/gen_bodies.h
        misc/inputparser.cpp
        misc/inputparser.h
        misc/model.cpp
        misc/model.h
        misc/mpi_types.cpp
        misc/mpi_types.h
        misc/readwrite.cpp
        misc/readwrite.h
        misc/utils.cpp
        misc/utils.h
        tree/build_tree.cpp
        tree/build_tree.h
        tree/orb.cpp
        tree/orb.h
        tree/tree.cpp
        tree/tree.h
        main.cpp)

add_executable(n_body ${SOURCE_FILES})