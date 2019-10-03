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

void json_herczig::json::OpenPattern()
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
        return;
    }
    while(getline(fileHand,lineFromFile))
        pattern.push_back(lineFromFile);

    fileHand.close();

}

uint8_t json_herczig::json::regexmatcherForDevType(std::string& temp)
{
    uint8_t result;
    if(regex_match(temp, this->devPattern.sensorPattern))
        result = Sensor;

    else if(regex_match(temp, this->devPattern.actuatorPattern))
        result = Actuator;

    else if(regex_match(temp, this->devPattern.sensorActuatorPattern))
        result = Sensor_Actuator;

    else
        result = Unknow_device;

    return result;
}

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

            this->deviceNumber++;

        else if( std::string::npos !=temp.find("devtype"))
        {
            size_t dev;
            dev = regexmatcherForDevType(temp);
            this->devicetype.push_back(dev);
        }

        else if( std::string::npos !=temp.find("commtype"))
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
        }
        pattern.erase(pattern.begin());
    }


}


void json_herczig::json::FinishProcess()
{
    while(deviceNumber)
    {
        std::cout << devicetype[deviceNumber-1] << std::endl;
        std::cout << commtype[deviceNumber-1] << std::endl;
        std::cout << (std::string)name[deviceNumber-1] << std::endl;
        std::cout << id[deviceNumber-1] << std::endl;
        deviceNumber--;
    }
}
