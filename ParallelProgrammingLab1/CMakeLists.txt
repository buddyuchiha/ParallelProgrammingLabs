cmake_minimum_required(VERSION 3.15)
project(ParallelProgrammingLab1)

set(MPI_HOME "C:/Program Files (x86)/Microsoft SDKs/MPI")
set(MPI_INCLUDE_PATH "${MPI_HOME}/Include")
set(MPI_LIBRARIES "${MPI_HOME}/Lib/x64/msmpi.lib")

if(NOT EXISTS ${MPI_INCLUDE_PATH})
    message(FATAL_ERROR "MPI Include not found: ${MPI_INCLUDE_PATH}")
endif()

if(NOT EXISTS ${MPI_LIBRARIES})
    message(FATAL_ERROR "MPI Library not found: ${MPI_LIBRARIES}")
endif()

add_executable(ParallelProgrammingLab1 ParallelProgrammingLab1.cpp)

target_include_directories(ParallelProgrammingLab1 PRIVATE ${MPI_INCLUDE_PATH})
target_link_libraries(ParallelProgrammingLab1 PRIVATE ${MPI_LIBRARIES})

message(STATUS "MPI configured successfully!")