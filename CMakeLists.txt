cmake_minimum_required(VERSION 3.25)
project(Living_World_New)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Living_World_New
        Organisms/Species/Organism.cpp
        Organisms/Species/Organism.h
        Organisms/Species/Plant.cpp
        Organisms/Species/Plant.h
        Living_World.cpp
        Utils/World.h Utils/World.cpp Utils/Position.cpp Utils/Position.h Organisms/Species/Animal.cpp Organisms/Species/Animal.h Organisms/Plants/Grass.h Organisms/Plants/Grass.cpp Organisms/Plants/Dandelion.cpp Organisms/Plants/Dandelion.h Organisms/Plants/Toadstool.h Organisms/Plants/Toadstool.cpp Organisms/Animals/Sheep.cpp Organisms/Animals/Wolf.cpp Organisms/Animals/Wolf.h)
