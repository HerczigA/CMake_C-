#pragma once 

#ifndef DEBUG_DEVICE
    #define DEBUG_DEVICE 0
#endif

#ifndef MAX_PORTS_NUMBER
    #define MAX_PORTS_NUMBER 21
#endif

#ifndef MAX_DC
    #define MAX_DC 1024
#endif

#ifndef PWM_RANGE_MAX
    #define PWM_RANGE_MAX 100
#endif

#ifndef MAX_SERVO_PORTS
    #define MAX_SERVO_PORTS 8
#endif

#ifndef SERVO_STEP
    #define SERVO_STEP 200
#endif

#ifndef SERVO_HIGH_LIMIT
    #define SERVO_HIGH_LIMIT 1050
#endif

#ifndef SERVO_LOW_LIMIT
    #define SERVO_LOW_LIMIT -150
#endif

#ifndef MIN_SERVO_DELAY_TIME
    #define MIN_SERVO_DELAY_TIME 100
#endif

#ifndef DEF_SERVO_TIME
    #define DEF_SERVO_TIME 200
#endif

#ifndef DEF_SERVO_POSITION
    #define DEF_SERVO_POSITION 500
#endif

#ifndef BUTTON_READ_TIME
    #define BUTTON_READ_TIME 50
#endif

#ifndef MAX_DEV_TYPE
    #define MAX_DEV_TYPE 3
#endif

#ifndef SPI_PACKET_LENGTH
    #define SPI_PACKET_LENGTH 8
#endif

#ifndef MAX_SPI_CLK
    #define MAX_SPI_CLK 1000000 //MAX speed 1MHz
#endif

#ifndef MAX_SPI_CHANNELS
    #define MAX_SPI_CHANNELS 2
#endif

#ifndef I2C_MAX_SPEED
    #define I2C_MAX_SPEED 400000
#endif

#ifndef I2C_MAX_PACKET_LENGTH
    #define I2C_MAX_PACKET_LENGTH 16
#endif

#include <stdint.h>
#include <iostream>
#include <string>
#include <syslog.h>
#include <vector>
#include <errno.h>
#include <error.h>
#include <memory>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <bits/stdc++.h>
#include <wiringPi.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

using  devType_t = uint8_t;
using namespace std;


using Id_t = uint16_t;
using comm_t = uint8_t;
using time_ms_t = unsigned int;
using display_Type_t = uint8_t;
using pwm_t = uint8_t;
using sens_type_t = uint8_t;
using devType_t = uint8_t;

enum comm_type
{
    SPI = 1,
    UART,
    I2C,
    PWM,
    Bluetooth,
    Unknown_communication,
    COMMTYPE

};

enum pwm_type
{
    simplePWM = 0,
    ServoPWM,
    UnknowPWM,
    PWMTYPE
};

enum pwm_err_t
{
    E_INIT_OK = 0,
    E_INIT_NOK,
    E_DC_OFLOW,
    E_DC_UFLOW,
    E_FREQ,
    E_UNKNOW

};

enum dev_type
{
    SENSOR = 1,
    ACTUATOR,
    SENSOR_ACTUATOR,
    DISPLAY,
    Unknown_device,
    DEVTYPE
};

enum sensor_type
{
    Button = 1,
    Humidity,
    Temperature,
    Distance,
    IRDA_Reciver,
    UNKNOW_SENSOR,
    SENSOR_TYPE
};

enum display_type
{
    LCD = 1,
    ST7735,
    _480x640_,
    DotMatrix,
    _7_segments,
    Unknow_display,
    DISPLAY_TYPE
};
