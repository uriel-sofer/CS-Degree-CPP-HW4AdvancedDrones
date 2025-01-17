cmake_minimum_required(VERSION 3.30)
project(HW4AdvancedDrones)

set(CMAKE_CXX_STANDARD 20)

add_executable(HW4AdvancedDrones main.cpp
        DirectionalVector.cpp
        DirectionalVector.h
        Drone.cpp
        Drone.h
        FileHandler.cpp
        FileHandler.h
        ForestIndex.cpp
        ForestIndex.h
        Point.cpp
        Point.h
        Simulation.cpp
        Simulation.h
        Vector.h
        SingleRotor.cpp
        SingleRotor.h)
