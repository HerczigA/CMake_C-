cmake_minimum_required(VERSION 3.6)

set(PROJECT "RPI_tutorial")
project(${PROJECT})

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)

endif()

#    file(GLOB SUBFILES src/*.cpp hdr/*.hpp main.cpp Communication/*.cpp Communication/*.hpp)
#if(__DEBUG)
#    set(CMAKE_C_FLAGS "-Wall -g")
#endif()
    set(SOURCES Communication/i2c_module.cpp
    Communication/spi_module.cpp
    Communication/uart_module.cpp
		src/device.cpp
    JSON/json.cpp
		main.cpp)

    set(HEADERS Communication/communication.hpp
		
    JSON/json.hpp
		hdr/device.hpp)

    message(STATUS "These are the sources :" ${SOURCES})
    message(STATUS "And headers: " ${HEADERS})

find_library(wiringPi_LIB wiringPi)

add_executable(${PROJECT} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT} ${wiringPi_LIB} pthread)
