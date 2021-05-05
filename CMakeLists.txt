cmake_minimum_required(VERSION 3.17)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp client.cpp Garage.cpp Vehicle.cpp Worker.cpp)