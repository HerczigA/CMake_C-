#ifndef _TEST_H_
#define _TEST_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../Communication/communication.hpp"
#include <wiringPi.h>
#include <unistd.h>
#include <fcntl.h>

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

using namespace std;

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
typedef uint8_t pwm_t;

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
    E_UNKNOW

};

enum dev_type
{
    Sensor = 1,
    Actuator,
    Sensor_Actuator,
    Unknow_device,
    DEVTYPE
};


class device
{
    protected:
        Id_t id;
        comm_t commType;
        string name;
        devType_t dev_Type;
        vector<uint8_t> pins;
        vector<uint8_t> dirs;
        uint8_t *directions;

        bool device_Initialized;
        bool communication_Initialized;
        Communication_c com;

    public:
        device();
        device(string Name, Id_t ID, devType_t devtype,comm_t commtype);
        ~device();
        uint8_t setPins(vector<uint8_t> pinNumbers);
        string &get_Name();
        devType_t get_Dev_Type();
        Id_t get_ID();
        comm_t get_Comm_Type();
        uint8_t get_PinNumbers();
        uint8_t get_Pin(int i);
        vector<uint8_t> &get_Pins();
        uint8_t get_Dirs(int i);
        void setName(string &devName);
        void setID(Id_t id);
        void setdevType(devType_t dev);
        void setcommType(comm_t commType);
        void setPinNumbers(uint8_t pins);
        void setPinsForuC(uint8_t pins, uint8_t dirs);
        int InitDevice();
};

class sensor : public device
{
    bool buttonPushed;
    bool prevButtonState;
    bool buttonState;
    public:
        sensor(string Name, Id_t ID, devType_t devtype, comm_t commtype) : device(Name,ID,devtype,commtype) {
            buttonPushed = false;
            buttonState = LOW;
            prevButtonState = LOW;
        }
        sensor() : device() {};
        void digital_Read(int pin);
        bool getButtonState();
        bool buttonStateChanged();
};

class actuator : public device
{
        int pwmRange ;
        int initValue ;

      public:
        actuator(string Name, Id_t ID, devType_t devtype, comm_t commtype) : device(Name,ID,devtype,commtype) {
            pwmRange = PWM_RANGE_MAX;
            initValue = 0;
        }
        actuator() : device() {};
        pwm_t pwm_Setup(vector<uint8_t> pinNumber);
        pwm_t pwm_ServoSetup(vector<uint8_t> pinNumbers,  uint8_t numberOfPorts);
        pwm_t Init_PWM(int pwm, vector<uint8_t> pinNumbers, uint8_t numberOfPorts);
        void digital_Write(vector<int> pinNumbers,vector<int> states);
        void pwm_Write(uint8_t pinNumber, int DC, time_ms_t  lengthOfDelay);
        void pwm_Write_Breathing(uint8_t pinNumber, time_ms_t  lengthOfDelay);
        void pwm_Servo_Write_In_Loop(uint8_t pinNumber, int16_t DC, time_ms_t lengthOfDelay, bool loop);
        void pwm_Servo_Full_Limit(uint8_t pinNumber,time_ms_t t_length);
        void pwm_Servo_Full_Limit(uint8_t pinNumber, time_ms_t t_length, bool button);

};


#endif
