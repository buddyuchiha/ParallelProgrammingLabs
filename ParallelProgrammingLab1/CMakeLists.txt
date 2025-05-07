cmake_minimum_required(VERSION 3.15) 

project(ParallelProgrammingLab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

add_executable(ParallelProgrammingLab1 "ParallelProgrammingLab1.cpp")

if(OpenMP_CXX_FOUND)
    target_link_libraries(ParallelProgrammingLab1 PRIVATE OpenMP::OpenMP_CXX)
endif()

