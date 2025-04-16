cmake_minimum_required(VERSION 3.15) 

project(ParallelProgrammingLab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    "*.cpp"
)


add_executable(ParallelProgrammingLab1 ${SOURCES})

