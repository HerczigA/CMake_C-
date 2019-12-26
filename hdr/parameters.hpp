#ifndef _PARAMETERS_HPP_
#define _PARAMETERS_HPP_


#define DEBUG_DEVICE 0

#define MAX_PORTS_NUMBER 21
#define MAX_DC 1024
#define PWM_RANGE_MAX 100

#define MAX_SERVO_PORTS 8
#define SERVO_STEP 200
#define SERVO_HIGH_LIMIT 1050
#define SERVO_LOW_LIMIT -150
#define MIN_SERVO_DELAY_TIME 100
#define DEF_SERVO_TIME 200
#define DEF_SERVO_POSITION 500

#define BUTTON_READ_TIME 50


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
}

enum display_type
{
    LCD = 1,
    ST7735,
    _480x640_,
    DotMatrix,
    _7_segments,
    Unknow_display,
    DISPLAY_TYPE
}


#endif