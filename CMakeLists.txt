cmake_minimum_required(VERSION 3.6)

set(PROJECT "RPI_tutorial")
project(${PROJECT})

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)

endif()

    file(GLOB SUBFILES src/*.cpp hdr/*.hpp main.cpp)
#    set(CMAKE_C_FLAGS "-Wall -g")
    message(STATUS "YOLO " ${SUBFILES})

find_library(wiringPi_LIB wiringPi)

add_executable(${PROJECT} ${SUBFILES})

target_link_libraries(${PROJECT} ${wiringPi_LIB} pthread)
