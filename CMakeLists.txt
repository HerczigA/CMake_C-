cmake_minimum_required(VERSION 3.6)

option(ENABLE_CROSS_COMPILE "CROSS_COMPILE")

if(${ENABLE_CROSS_COMPILE})
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/tools/raspberry.cmake)
  message(STATUS "Using toolchain file :${CMAKE_TOOLCHAIN_FILE}")
else()
  message(STATUS "Do not using toolchain file")
endif()


set(PROJECT "RPI_IOT")
project(${PROJECT})

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

#     # pwm/pwm.cpp
#     # displays/display.cpp

file(GLOB SOURCES Communication/*.cpp 
    device/device.cpp
    mainApp/mainApp.cpp
    JSON/json.cpp
    main.cpp
    )

file(GLOB HEADERS Communication/*.h 
    device/device.h
    mainApp/mainApp.h
    JSON/json.h
    util/parameters.h
    )
#   # pwm/pwm..

message(STATUS "These are the sources :" ${SOURCES})
message(STATUS "And headers: " ${HEADERS})

find_library(WIRINGPI_LIB wiringPi)

find_package(nlohmann_json 3.11.2 REQUIRED)

add_executable(${PROJECT} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT} ${WIRINGPI_LIB} pthread nlohmann_json::nlohmann_json)

target_include_directories(${PROJECT} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/mainApp
    ${CMAKE_CURRENT_SOURCE_DIR}/device
    ${CMAKE_CURRENT_SOURCE_DIR}/Communication
    ${CMAKE_CURRENT_SOURCE_DIR}/database
    ${CMAKE_CURRENT_SOURCE_DIR}/JSON
    ${CMAKE_CURRENT_SOURCE_DIR}/util

)
