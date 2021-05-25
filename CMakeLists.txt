cmake_minimum_required(VERSION 3.17)
project(Project)

#set(CMAKE_CXX_STANDARD 14)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#if (WIN32)
  #  include_directories("$ENV{SFML_PATH}/include")
 #   link_directories("$ENV{SFML_PATH}/lib")
#endif()

#
include_directories(fasterServices)
include_directories(graph)
include_directories(include)
include_directories(utilities)
include_directories(resources)

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)


add_executable(project main.cpp fasterServices/client.cpp fasterServices/Garage.cpp fasterServices/Vehicle.cpp fasterServices/Worker.cpp  graph/Graph.h utilities/Position.cpp utilities/Position.h utilities/MutablePriorityQueue.h utilities/exception.h GraphImporter.cpp include/GraphImporter.h GraphMaker.cpp include/GraphMaker.h include/Solver.h Solver.cpp)
target_link_libraries(project graphviewer)