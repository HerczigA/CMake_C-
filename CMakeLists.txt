cmake_minimum_required(VERSION 3.6)

set(PROJECT "RPI_IOT")
project(${PROJECT})

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)
    set(CMAKE_CXX_STANDARD 17)

endif()

#get_filename_component(RPI_IOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ ABSOLUTE)

#list(APPEND CMAKE_MODULE_PATH ${RPI_IOT_PATH}/main_Init/)
#message(STATUS "CMAKE_MODULE_PATH " ${CMAKE_MODULE_PATH})
#add_library(main_Init)


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

# find_library(wiringPi_LIBRARIES wiringPi)

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

add_executable(${PROJECT} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT} ${WIRINGPI_LIBRARIES} pthread)

target_include_directories(${PROJECT} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/mainApp
    ${CMAKE_CURRENT_SOURCE_DIR}/device
    ${CMAKE_CURRENT_SOURCE_DIR}/Communication
    ${CMAKE_CURRENT_SOURCE_DIR}/database
    ${CMAKE_CURRENT_SOURCE_DIR}/JSON
    ${CMAKE_CURRENT_SOURCE_DIR}/util

)
