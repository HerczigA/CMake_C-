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
                DIRS.push_back("IN");
                DIRS.push_back("OUT");
                
};

json_herczig::json::json()
{   
                deviceNumber = 0;
                comPattern.SPIPattern = std::regex("(SPI)|(spi)]");
                comPattern.I2CPattern = std::regex("(I2C)|(i2c)");
                comPattern.UARTPattern = std::regex("(UART)|(uart)");
                comPattern.PWMPattern = std::regex("(pwm)|(PWM)");
                comPattern.BluetoothPattern = std::regex("Bluetooth");
                DIRS.push_back("IN");
                DIRS.push_back("OUT");
                
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
void json_herczig::json::checkIO(std::string &text)
{
    
    int dircnt = 0;
    size_t found = text.find_last_of(":");
    text = text.substr(found+1);
    if( text.end() != std::find_if(text.begin(),text.end(),[] (char c)
        {  return (c == '[' ); }   ))
    {
        text.erase(text.begin());
        auto tEnd = text.end();
        for(auto it = text.begin();it != tEnd; ++it)
        {
            //INPUT
            found = text.find(DIRS[0]); 
            if(std::string::npos != found)
            {
                directions.push_back(1);
                text = text.substr(found + DIRS[0].length());
                it = text.begin();
                dircnt++;
                continue;
            }
            found = text.find(DIRS[1]);
            if(std::string::npos != found)
            {
                directions.push_back(0);
                text = text.substr(found + DIRS[1].length());
                it = text.begin();
                dircnt++;
                continue;
            }
            else
                break;
        }
    }
    std::cout <<dircnt << std::endl;
    if(dircnt)
        directions_Offset.push_back(dircnt);
    else
        ;//TODO: LOG

}

int json_herczig::json::calculatePinNumbers(std::string &text)
{
    text.erase(text.begin());
    bool twoDigit = true;
    int pins = 0;
    for(const char* p = text.c_str(); *p ; p++)
    {
        
        if(*p >='0' && *p <= '9' && twoDigit)
        {
            pinNumbers.push_back(atoi(p));
            pins++;
            p++;
            if(*p >= '0' && *p <= '9')
            {
                twoDigit = false;
                p -= 1;    
            }

        }
        else
            twoDigit = true;
    }
    return pins;

}
uint8_t json_herczig::json::regexmatcherForComType(std::string& temp)
{
    uint8_t result = 0;
    if(regex_search(temp, comPattern.SPIPattern))
        result = SPI;

    else if(regex_search(temp, comPattern.I2CPattern))
        result = I2C;

    else if(regex_search(temp, comPattern.UARTPattern))
        result = UART;

    else if(regex_search(temp, comPattern.PWMPattern))
        result = PWM;

    else if(regex_search(temp, comPattern.BluetoothPattern))
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


         if( std::string::npos !=temp.find("Device" ))
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
                        SensorsAndActuators++;
                        devicetype.push_back(Sensor_Actuator);
                        checkDevicetype = false;
                    }

                    else if(std::string::npos != temp.find("Sensor"))
                    {
                        Sensors++;
                        devicetype.push_back(Sensor);
                        checkDevicetype = false;
                    }

                    else if(std::string::npos != temp.find("Actuator"))
                    {
                        Actuators++;
                        devicetype.push_back(Actuator);
                        checkDevicetype = false;
                    }

                    else if( tempEnd != std::find_if(temp.begin(),tempEnd,[] (char c)
                    {  return (c == '{') || (c =='}') ; }   ))
                        ;
                        
                    else
                    {
                        std::cout << temp << std::endl;
                        devicetype.push_back(Unknow_device);
                    }
                        

                }
                else
                {
                    if( std::string::npos !=temp.find("commtype"))
                    {
                        size_t dev;
                        dev = regexmatcherForComType(temp);
                        commtype.push_back(dev);
                    }
                    else if( std::string::npos !=temp.find("name"))
                    {

                        found = temp.find_last_of(":");
                        temp = temp.substr(found+1);
                        temp.erase(0,2);
                        temp.erase(temp.end()-2,temp.end()-0);
                        name.push_back(temp);
                    }
                    else if( std::string::npos !=temp.find("pin(s)"))
                    {
                        int pins = 1;
                        found = temp.find_last_of(":");
                        temp = temp.substr(found+1);
                        if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (char c)
                            {  return (c == '[' ); }   ))
                        {
                            pins = calculatePinNumbers(temp);
                        }
                        
                        else
                        {
                            temp.erase(temp.begin()+1);
                            pinNumbers.push_back(atoi(temp.c_str()));
                        }

                        pinOffset.push_back(pins);
                    }
                    else if( std::string::npos !=temp.find("dir"))
                    {
                        checkIO(temp);
                    }
                    else if( std::string::npos !=temp.find("ID"))
                    {
                        found = temp.find_last_of(":");
                        temp = temp.substr(found+1);
                        temp.erase(temp.begin()+1);
                        id.push_back(atoi(temp.c_str()));
                        checkDevicetype = true;
                    }
                }
                pattern.erase(pattern.begin());
                temp=pattern[0];
            }


        }
        pattern.erase(pattern.begin());
    }

    deviceNumber = Actuators + Sensors + SensorsAndActuators;
    
#if DEBUG
    std::cout << "Device number: " <<(int) deviceNumber
     << "\nActuator number:  " <<(int) Actuators
     << "\nSensor number: " <<(int) Sensors
     << "\nnSensor&Actuator number: " << (int)SensorsAndActuators<< std::endl;
     for(auto it = pinNumbers.begin(); it != pinNumbers.end(); ++it)
    {
        std::cout << "pinNumbers: " <<*it << std::endl;
    }
#endif    
}

void json_herczig::json::FinishProcess()
{
    std::cout << "Details about devices after read" << std::endl;
    size_t i = 0;
    while(i < deviceNumber)
    {
       
        std::cout << std::endl;
        std::cout << "ID: " << id[i] << std::endl;
        std::cout << "Name: " << (std::string)name[i] << std::endl;
        std::cout << "Devicetype: " << devicetype[i] << std::endl;
        std::cout << "CommType: " << commtype[i] << std::endl;
        if(pinOffset[i])
        {
            std::cout << "pinOffset[i]: " << pinOffset[i] << std::endl;
            for(size_t j = 0; j < pinOffset[i]; j++)
            {
                std::cout << "Pins: " << pinNumbers[i+j] << std::endl;
            }
        }
        else   
            std::cout << "Pins: " << pinNumbers[i] << std::endl;
        
        std::cout << std::endl;
        i++;
    }
}

json_herczig::json::~json()
{
    name.clear();
    devicetype.clear();
    commtype.clear();
    id.clear();

}
