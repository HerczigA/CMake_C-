cmake_minimum_required(VERSION 3.6)

set(PROJECT "RPI_IOT")
project(${PROJECT})

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)
    set(CMAKE_CXX_STANDARD 17)

endif()

get_filename_component(RPI_IOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ ABSOLUTE)

list(APPEND CMAKE_MODULE_PATH ${RPI_IOT_PATH}/main_Init/)
message(STATUS "CMAKE_MODULE_PATH " ${CMAKE_MODULE_PATH})
#add_library(main_Init)


set(SOURCES Communication/i2c_module.cpp
    Communication/spi_module.cpp
    Communication/uart_module.cpp
    src/device.cpp
    main_Init/main_Init.cpp
    JSON/json.cpp
    main.cpp)

set(HEADERS Communication/communication.hpp
  main_Init/main_Init.hpp
  JSON/json.hpp
  hdr/device.hpp)

message(STATUS "These are the sources :" ${SOURCES})
message(STATUS "And headers: " ${HEADERS})

find_library(wiringPi_LIB wiringPi)

add_executable(${PROJECT} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT} ${wiringPi_LIB} pthread)
