cmake_minimum_required(VERSION 3.7)
project(Moore)

set(SOURCE_FILES main.cpp Node.cpp Node.h AdjacencyTable.cpp AdjacencyTable.h Graph.cpp Graph.h Dijkstra.cpp Dijkstra.h MPIBase.cpp MPIBase.h Moore.cpp Moore.h)
set(CMAKE_CXX_COMPILER /usr/local/bin/mpic++)
set(CMAKE_CXX_STANDARD  11)
INCLUDE_DIRECTORIES(/usr/local/include)
add_executable(Moore ${SOURCE_FILES})