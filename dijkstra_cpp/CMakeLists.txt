cmake_minimum_required(VERSION 3.27)

project(DijkstraAlgorithm)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(inc)

add_executable( dijkstra
    src/dijkstra.cpp
    src/main.cpp
)