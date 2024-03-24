cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(normal_distributions_transform)

set(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE(PCL REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread filesystem)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


add_executable(normal_distributions_transform normal_distributions_transform.cpp )
target_link_libraries (normal_distributions_transform ${PCL_LIBRARIES} ${Boost_LIBRARIES})
