#pragma once

#include "communication.h"
#include "parameters.h"


typedef uint8_t pwm_t;

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
        // int pwmRange ;
        int initValue ;

      public:
        actuator(string Name, Id_t ID, devType_t devtype, comm_t commtype) 
        : device(Name,ID,devtype,commtype) 
        {
            // pwmRange = PWM_RANGE_MAX;
            initValue = 0;
        }
        actuator() : device() {};
        // pwm_t pwm_Setup(vector<uint8_t> pinNumber);
        // pwm_t pwm_ServoSetup(vector<uint8_t> pinNumbers,  uint8_t numberOfPorts);
        // pwm_t Init_PWM(int pwm, vector<uint8_t> pinNumbers, uint8_t numberOfPorts);
        // void digital_Write(vector<int> pinNumbers,vector<int> states);
        // void pwm_Write(uint8_t pinNumber, int DC, time_ms_t  lengthOfDelay);
        // void pwm_Write_Breathing(uint8_t pinNumber, time_ms_t  lengthOfDelay);
        // void pwm_Servo_Write_In_Loop(uint8_t pinNumber, int16_t DC, time_ms_t lengthOfDelay, bool loop);
        // void pwm_Servo_Full_Limit(uint8_t pinNumber,time_ms_t t_length);
        // void pwm_Servo_Full_Limit(uint8_t pinNumber, time_ms_t t_length, bool button);

};
