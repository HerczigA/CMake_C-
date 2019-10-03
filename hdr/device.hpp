#ifndef _TEST_H_
#define _TEST_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../Communication/spi_module.hpp"
#include "../Communication/i2c_module.hpp"
#include "../Communication/uart_module.hpp"
#include <wiringPi.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_PORTS_NUMBER 21
#define MAX_SERVO_PORTS 8
#define MAX_DC 1024
#define SERVO_STEP 200
#define SERVO_HIGH_LIMIT 1050
#define SERVO_LOW_LIMIT -150
#define MIN_SERVO_DELAY_TIME 100
#define DEF_SERVO_TIME 200
#define DEF_SERVO_POSITION 500
#define PWM_RANGE_MAX 100

typedef uint8_t devType_t;
typedef uint16_t Id_t;
typedef uint8_t comm_t;
typedef unsigned int time_ms_t;

using namespace std;

static uint16_t id_counter =1;

enum comm_type
{
    SPI = 1,
    //CAN,
    UART,
    I2C,
    PWM,
    Bluetooth,
    //Wifi,
    Unknow_communication,
    COMMTYPE

};

enum dev_type
{
    Sensor = 1,
    Actuator,
    Sensor_Actuator,
    Unknow_device,
    DEVTYPE
};


struct Communications
{
    SPI_Frame spi;
    I2C_Frame i2c;
    term serialport;
};

class foo
{
    public:
    int i;
    foo() : i{10} {}
    foo(int const i_) : i{i_} {}
    auto getFooInt(){ return i;}
};


class device
{
    protected:
        Communications COM;
        Id_t id;
        comm_t commType;
        string name;
        devType_t dev_Type;


        bool device_Initialized;
        bool communication_Initialized;
        spi_error Init_SPI(SPI_Frame spi);
        i2c_error_t Init_I2C(I2C_Frame i2c);
        int Init_Bluetooth();
        int Init_UART();
        //int Init_CAN();
        //int Init_Wifi();

    public:
        device(string Name, Id_t ID, devType_t devtype,comm_t commtype): name{Name}
        {
            id =( !ID && id_counter != 1 ) ? id_counter : id_counter++;
            dev_Type = (devtype >= Sensor && devtype <= Sensor_Actuator) ? devtype : Unknow_device;
            commType = (commtype >= SPI && commtype <= Bluetooth) ? commtype : Unknow_communication;
            wiringPiSetup();
            device_Initialized = false;
        }
        string get_Name();
        devType_t get_Dev_Type();
        Id_t get_ID();
        comm_t get_Comm_Type();
        uint8_t setPins(vector<uint8_t> pinNumbers,uint8_t directions[], uint8_t numberOfPorts);
        void Init_Communication();
};

class sensor : public device
{
    bool buttonPushed;
    public:
        sensor(string Name, Id_t ID, devType_t devtype, comm_t commtype) : device(Name,ID,devtype,commtype) {
            buttonPushed = false;
        }
        void digital_Read(int pin);
        bool getButtonState();

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
        void pwm_Setup(int pinNumber);
        void pwm_ServoSetup(vector<uint8_t> pinNumbers,  uint8_t numberOfPorts);
        void digital_Write(vector<int> pinNumbers,vector<int> states);
        void pwm_Write(uint8_t pinNumber, int DC, time_ms_t  lengthOfDelay);
        void pwm_Write_Breathing(uint8_t pinNumber, time_ms_t  lengthOfDelay);
        void pwm_Servo_Write_In_Loop(uint8_t pinNumber, int16_t DC, time_ms_t lengthOfDelay, bool loop);
        void pwm_Servo_Full_Limit(uint8_t pinNumber,time_ms_t t_length);

};


#endif
