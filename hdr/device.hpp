#ifndef _TEST_H_
#define _TEST_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../Communication/communication.hpp"
#include "parameters.hpp"
#include "../pwm/pwm.hpp"
#include "../displays/display.hpp"
#ifdef RPI_VERSION
    #include <wiringPi.h>
#endif
#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include <algorithm>
#include <iterator>
#include <bits/stdc++.h>

using namespace std;

class device
{
    protected:
        Id_t id;
        comm_t commType;
        string name;
        devType_t dev_Type;
        Communication_c com;
        //pair pins-dirs??
        vector<uint8_t> pins;
        vector<uint8_t> dirs;
        uint8_t *directions;

        bool device_Initialized;
        bool communication_Initialized;
        

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
        //int InitDevice();
};

class sensor : public device
{
    sens_type_t Sensor;
    bool buttonPushed;
    bool prevButtonState;
    bool buttonState;
    public:
        sensor(string Name, Id_t ID, devType_t devtype, comm_t commtype) : device(Name,ID,devtype,commtype) {
            if(Sensor == Button)
            {
                buttonPushed = false;
                buttonState = LOW;
                prevButtonState = LOW;
            }
            
        }
        sensor() : device() {};
        void digital_Read_For_Button(int pin);
        bool getButtonState();
        bool buttonStateChanged();
};

class actuator : public device
{
    
      public:
      std::unique_ptr<PWMclass> pwmObj;
        actuator(string Name, Id_t ID, devType_t devtype, comm_t commtype, pwm_t *pwmtype) : device(Name,ID,devtype,commtype)
        {
            if(*pwmtype)
            {
                pwmObj = std::make_unique<PWMclass>();
                pwmObj->set_pwm_Type(*pwmtype);
                uint8_t pinSize  = pins.size();
                pwmObj->Init_PWM(*pwmtype, pins, pinSize);

            }
            
        }
        actuator() : device() {};
        void digital_Write(vector<int> pinNumbers,vector<int> states);
       

};

class display 
{
    display_Type_t displayType;

    public:
        display();
    

};

#endif
