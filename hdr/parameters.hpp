#ifndef _PARAMETERS_HPP_
#define _PARAMETERS_HPP_

#include <stdint.h>
#include <memory>
#include <unistd.h>
#include <algorithm>
#include <iterator>
#include <bits/stdc++.h>
#include <wiringPi.h>
#include <time.h>

#define BUTTON_READ_TIME 50

#define RPI_VERSION 1
#define TEST_DISPLAY_LCD 1
#define DEBUG_DEVICE 0
#define ARDUINO 0
typedef uint8_t devType_t;
typedef uint16_t Id_t;
typedef uint8_t comm_t;
typedef unsigned int time_ms_t;
typedef uint8_t display_Type_t;
typedef uint8_t pwm_t;
typedef uint8_t sens_type_t;

enum comm_type
{
    SPI = 1,
    UART,
    I2C,
    PWM,
    Bluetooth,
    Unknow_communication,
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
    E_INIT_NOK= -1,
    E_INIT_OK = 0,
    E_DC_OFLOW,
    E_DC_UFLOW,
    E_FREQ,
    E_UNKNOW

};

enum dev_type
{
    SENSOR = 1,
    ACTUATOR,
    uC,
    DISPLAY,
    Unknow_device,
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
    Unknow_display = 0,
    LCD = 1,
    TFT_ST7735,
    _480x640_,
    DotMatrix,
    _7_segments,
    DISPLAY_TYPE
};


#endif