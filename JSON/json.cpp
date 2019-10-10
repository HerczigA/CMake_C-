#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <regex>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "json.hpp"
#include <string>

using namespace std;

json_herczig::json::json(const char &p): jsonFile{&p}
{
                deviceNumber = 0;
                comPattern.SPIPattern = std::regex("(SPI)|(spi)]");
                comPattern.I2CPattern = std::regex("(I2C)|(i2c)");
                comPattern.UARTPattern = std::regex("(UART)|(uart)");
                comPattern.PWMPattern = std::regex("(pwm)|(PWM)");
                comPattern.BluetoothPattern = std::regex("Bluetooth");
};

json_herczig::json::json()
{   
                deviceNumber = 0;
                comPattern.SPIPattern = std::regex("(SPI)|(spi)]");
                comPattern.I2CPattern = std::regex("(I2C)|(i2c)");
                comPattern.UARTPattern = std::regex("(UART)|(uart)");
                comPattern.PWMPattern = std::regex("(pwm)|(PWM)");
                comPattern.BluetoothPattern = std::regex("Bluetooth");
};
bool json_herczig::json::OpenPattern()
{
    try
    {
        fileHand.open(jsonFile.c_str(), ios::in);
        if(!fileHand.is_open())
            throw "can not open the file";
    }
    catch(char const* msg)
    {
        std::cout << msg << "\nException under opening" << endl;
        return false;
    }
    while(getline(fileHand,lineFromFile))
        pattern.push_back(lineFromFile);

    fileHand.close();
    processPattern();
    #if DEBUG
        FinishProcess();
    #endif
    return true;

}
/*
uint8_t json_herczig::json::regexmatcherForComType(std::string& temp)
{
    uint8_t result = 0;
    if(regex_search(temp, this->comPattern.SPIPattern))
        result = SPI;

    else if(regex_search(temp, this->comPattern.I2CPattern))
        result = I2C;

    else if(regex_search(temp, this->comPattern.UARTPattern))
        result = UART;

    else if(regex_search(temp, this->comPattern.PWMPattern))
        result = PWM;

    else if(regex_search(temp, this->comPattern.BluetoothPattern))
        result = Bluetooth;

    else
        result = Unknow_communication;

    return result;
}


void json_herczig::json::processPattern()
{

    size_t found;
    while(pattern.begin() != pattern.end())
    {

        auto temp = pattern[0];
        auto tempEnd =temp.end();

        if( tempEnd != std::find_if(temp.begin(),tempEnd,[] (char c)
            {  return (c == '{' || c == '}' ); }   ))
        ;


        else if( std::string::npos !=temp.find("Device" ))
        {
            pattern.erase(pattern.begin());
            temp = pattern[0];
            bool checkDevicetype = true;

            for(; std::string::npos == temp.find("}" ); )
            {
                if(checkDevicetype)
                {
                    if(std::string::npos != temp.find("Sensor_Actuator"))
                    {
                        this->SensorsAndActuators++;
                        devicetype.push_back(Sensor_Actuator);
                        checkDevicetype = false;
                        
                    }

                    else if(std::string::npos != temp.find("Sensor"))
                    {
                        this->Sensors++;
                        devicetype.push_back(Sensor);
                        checkDevicetype = false;
                    }

                    else if(std::string::npos != temp.find("Actuator"))
                    {
                        this->Actuators++;
                        devicetype.push_back(Actuator);
                        checkDevicetype = false;
                    }
                    //else
                      //  devicetype.push_back(Unknow_device);

                }
                else
                {
                    if( std::string::npos !=temp.find("commtype"))
                    {
                        size_t dev;
                        dev = regexmatcherForComType(temp);
                        this->commtype.push_back(dev);
                    }
                    else if( std::string::npos !=temp.find("name"))
                    {

                        found = temp.find_last_of(":");
                        temp = temp.substr(found+1);
                        temp.erase(0,2);
                        temp.erase(temp.end()-2,temp.end()-0);
                        this->name.push_back(temp);
                    }

                    else if( std::string::npos !=temp.find("ID"))
                    {
                        found = temp.find_last_of(":");
                        temp = temp.substr(found+1);
                        temp.erase(temp.begin()+1);
                        this->id.push_back(atoi(temp.c_str()));
                        checkDevicetype = true;
                    }
                }
                pattern.erase(pattern.begin());
                temp=pattern[0];
            }


        }
        pattern.erase(pattern.begin());


    }
#if DEBUG
    this->deviceNumber = this->Actuators + this->Sensors + this->SensorsAndActuators;
    std::cout << "Device number: " <<(int) this->deviceNumber
     << "\nActuator number:  " <<(int) this->Actuators
     << "\nSensor number: " <<(int) this->Sensors
     << "\nnSensor&Actuator number: " << (int)this->SensorsAndActuators<< std::endl;
#endif    
}


void json_herczig::json::FinishProcess()
{
    std::cout << "Details about devices after read" << std::endl;
    size_t i = 0;
    while(i < deviceNumber)
    {
       
        std::cout << std::endl;
        std::cout << "ID: " <<id[i] << std::endl;
        std::cout << "Name: " <<(std::string)name[i] << std::endl;
        std::cout << "Devicetype: " <<devicetype[i] << std::endl;
        std::cout << "CommType: " <<commtype[i] << std::endl;
        std::cout << std::endl;
        i++;
    }
}


json_herczig::json::~json()
{
    this->name.clear();
    this->devicetype.clear();
    this->commtype.clear();
    this->id.clear();

}
