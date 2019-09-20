cmake_minimum_required(VERSION 3.6)
project(Tutorial)

set(Tutorial_VERSION_MAJOR 1)
set(Tutorial_VERSION_MINOR 0)

if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)

endif()

    file(GLOB SUBFILES src/*.cpp hdr/*.hpp main.cpp)
#    set(CMAKE_C_FLAGS "-Wall -g")
    message(STATUS "YOLO " ${SUBFILES})

endif()

find_library(wiringPi_LIB wiringPi)

add_executable(Tutorial ${SUBFILES})

target_link_libraries(Tutorial ${wiringPi_LIB})
