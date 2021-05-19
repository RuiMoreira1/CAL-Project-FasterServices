cmake_minimum_required(VERSION 3.17)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp fasterServices/client.cpp fasterServices/Garage.cpp fasterServices/Vehicle.cpp fasterServices/Worker.cpp graph/Graph.cpp graph/Graph.h graph/Node.cpp graph/Node.h graph/Edge.cpp graph/Edge.h graph/Vertex.cpp graph/Vertex.h utilities/Position.cpp utilities/Position.h utilities/MutablePriorityQueue.h)