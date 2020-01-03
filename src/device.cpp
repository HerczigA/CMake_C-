#include "../hdr/device.hpp"
#include <iostream>
#include <string>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <bits/stdc++.h>
#include <softServo.h>
#include <softPwm.h>
using namespace std;

static Id_t id_counter = 1;

device::device(): device_Initialized{false}
{
    id = 0;
    directions = nullptr;
    dev_Type =  Unknow_device;
    commType =  Unknow_communication;
    wiringPiSetup();
}

device::device(string Name, Id_t ID, devType_t devtype,comm_t commtype): name{Name}, device_Initialized(false)
{
    directions = nullptr;
    id =( !ID && id_counter != 1 ) ? id_counter : id_counter++;
    dev_Type = (devtype >= SENSOR && devtype <= uC) ? devtype : Unknow_device;
    commType = (commtype >= SPI && commtype <= Bluetooth) ? commtype : Unknow_communication;
    wiringPiSetup();
}

device::~device()
{
    delete[] directions;
}

string &device::get_Name()
{
    return name;
}

devType_t device::get_Dev_Type()
{
    return dev_Type;
}

Id_t device::get_ID()
{
    return id;
}

comm_t device::get_Comm_Type()
{
    return commType;
}

uint8_t device::get_PinNumbers()
{
    return pins.size();
}

uint8_t device::get_Pin(int i)
{
    return pins[i];
}

vector<uint8_t> &device::get_Pins()
{
    return pins;
}

uint8_t device::get_Dirs(int i)
{
    return directions[i];
}

void device::setName(string &devName)
{
    name = devName;
}

void device::setdevType(devType_t dev )
{
    dev_Type = dev;
}

void device::setPinNumbers(uint8_t pins)
{
    this->pins.push_back(pins);
}

void device::setPinsForuC(uint8_t pins, uint8_t dirs)
{
    this->pins.push_back(pins);
    this->dirs.push_back(dirs);
}

void device::setID(Id_t id)
{
    if(!id || id < (id_counter-1) || id > id_counter)
        {

            this->id = id_counter;
            id_counter += 1;

            #if DEBUG_DEVICE
                cout << "in if setid  " << id << " id_counter: " << id_counter<< " id: "<<id<< endl;
            #endif
        }

    else
        {
            this->id = id;
            #if DEBUG_DEVICE
                cout << "in else setid  " << id << endl;
            #endif
        }

}

void device::setcommType(comm_t commType)
{
    this->commType = commType;
    int result = 0;
    switch(commType)
    {
        case SPI:
            result = com.Init_SPI(com.SerialCom.spi);
            if(result)
                syslog(LOG_ERR, " SPI setup : %d ", result);
            break;

        case I2C:
            result = com.Init_I2C(com.SerialCom.i2c);
            if(result)
                syslog(LOG_ERR, " I2C setup : %d ", result);
            break;

        /*case PWM:
            Init_PWM();
            if(result)
                syslog(LOG_ERR, " PWM setup : %d ", result);
            device_Initialized = true;
            break;*/

        case UART:
            result = com.Init_UART();
            if(result)
                syslog(LOG_ERR, " UART setup : %d ", result);
            break;

        case Bluetooth:
            //Init_Bluetooth();
            break;

        default:
            break;
    }
}


void sensor::digital_Read(int pin)
{
    if(pin >= MAX_PORTS_NUMBER)
        return;
        //should thrown exception

        if(digitalRead(pin))
        {
            delay(BUTTON_READ_TIME);
            buttonPushed = digitalRead(pin) ? true : false;
        }


        if(buttonPushed)
        {
#if DEBUG_DEVICE
            cout<< "button pushed" << endl;
#endif
            prevButtonState = buttonState;
            buttonState = !buttonState;

        }
        buttonPushed = false;

}

bool sensor::getButtonState()
{
    return buttonState;
}

bool sensor::buttonStateChanged()
{
    bool result = false;
    if(prevButtonState  != buttonState)
    {
        result = true;
        prevButtonState = buttonState;
        cout << "prevButtonState  != buttonState" << endl;
    }
    else
    {
        result = false;
    }

    return result;
}

uint8_t device::setPins(vector<uint8_t> pinNumbers)
{
    int result = 0;
    if(pinNumbers.empty() || pinNumbers.size() >= MAX_PORTS_NUMBER )
    {
         cout << "Nullpointer for pinNumbers or too much number for ports bastard!? " << endl;
         result = 1;
    }
    else
    {
        uint8_t i = 0;
        const size_t pinSize = pinNumbers.size();
        while(i < pinSize)
        {

            int j = 0 ;
            switch (dev_Type)
            {
                case SENSOR:
                    directions = new uint8_t[ pins.size()];
                    if(!directions)
                    {
                        cout<< "no memory for alloc directions " << endl;
                        result = 4;
                        break;
                    }
                    while(j <  pins.size())
                    {
                        directions[j] = INPUT;
                        j++;
                    }
                    break;

                case ACTUATOR:
                    directions = new uint8_t[pins.size()];
                    if(!directions)
                    {
                        cout<< "no memory for alloc directions " << endl;
                        result = 4;
                        break;
                    }
                    j = 0;

                    while(j < pins.size())
                    {
                        directions[j] = OUTPUT;
                        j++;

                    }
                    break;
                case uC:
                    directions = new uint8_t[pins.size()];
                    if(!directions)
                    {
                        cout<< "no memory for alloc directions " << endl;
                        result = 4;
                        break;
                    }
                    j = 0;
                    while(j < pins.size())
                    {

                        directions[j] = dirs[j] ? OUTPUT : INPUT;
                        j++;

                    }
                    break;

                default :
                    cout<< "default branch in setpins " << endl;
                    break;
            }
            //TODO: check the same size of pinnumbers and directions
	            pinMode(pinNumbers[i],directions[i]);
		        i++;

        }
    }
#if DEBUG_DEVICE
    cout << "result = "<< result << endl;
#endif
    return result;

}

void actuator::digital_Write(vector<int> pinNumbers, vector<int> states )
{
    if(pinNumbers.empty() || states.empty())
    {
        cout << "some arguments are empty" << endl;
    }
    if(pinNumbers.size() == states.size())
    {
        auto endOfVector = pinNumbers.end();

        for(auto it = pinNumbers.begin(); it != endOfVector; it++)
            digitalWrite(pinNumbers[*it],states[*it]) ;
    }
}
