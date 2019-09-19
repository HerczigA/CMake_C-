cmake_minimum_required(VERSION 3.6)
project(Tutorial)

set(Tutorial_VERSION_MAJOR 1)
set(Tutorial_VERSION_MINOR 0)

if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)

endif()

    file(GLOB SUBFILES src/*.cpp hdr/*.hpp main.cpp)
#    set(CMAKE_C_FLAGS "-Wall -g")
#    set(sources main.cpp src/test.cpp hdr/test.hpp)
#    set(headers hdr/test.hpp)
    message(STATUS "YOLO " ${SUBFILES})

if(NOT find_library(WIRINGPI_LIBRRIES PI wiringPi)
    add_definitions(-L//path/of/pilibrary -lwiringPi)

endif()
#add_library(src src/test.cpp)
#include_directories("${PROJECT_SOURCE_DIR}/src")
#add_subdirectory (src)


#set(INCLUDEDSHIT "/home/adam/Prog/cmakeC++/src/test.cpp" "/home/adam/Prog/cmakeC++/hdr/test.hpp" )

#target_include_directories(test PRIVATE ${INCLUDEDSHIT})

#add_executable(Tutorial ${sources} ${headers})
add_executable(Tutorial ${SUBFILES})
find_library(wiringPi_LIB wiringPi)
target_link_libraries(Tutorial ${wiringPi_LIB})
