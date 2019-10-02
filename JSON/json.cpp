#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <regex>
#include <stdlib.h>
#include "json.hpp"
#include "./hdr/device.hpp"

void json_herczig::json::OpenPattern()
{
    try
    {
        fileHand.open(jsonFile.c_str(), ios::in);
        
    }
    catch(fstream::failure e)
    {
        std::cerr << e.what() << '\n';
        std::cout << e.what() << "Exception under opening" << endl;
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
    if(regex_match(temp, this->comPattern.SPIPattern))
        result = SPI;
    
    else if(regex_match(temp, this->comPattern.I2CPattern))
        result = I2C;
    
    else if(regex_match(temp, this->comPattern.UARTPattern))  
        result = UART;
    
    else if(regex_match(temp, this->comPattern.PWMPattern))  
        result = PWM;

    else if(regex_match(temp, this->comPattern.BluetoothPattern))  
        result = Bluetooth;
    
    else
        result = Unknow_communication;
}


void json_herczig::json::processPattern()
{
  
    size_t found;
    auto endOfPattern = pattern.end();
    
    while(pattern.begin() != endOfPattern)
    {
        
        auto temp = pattern[0];
        if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (char c)
            {  return (c == '{' || c == '}' ); }   ))
            ;
        
        else if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (std::string str)
            {   return str == "Device"; }   ))
            this->deviceNumber++;   
        
        else if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (std::string str)
            {   return str == "devtype"; }   ))
        {
            size_t dev;
            dev = regexmatcherForDevType(temp);
            this->devicetype.push_back(dev);
        }
        
        else if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (std::string str)
            {   return str == "commtype"; }   ))
        {
            size_t dev;
            dev = regexmatcherForComType(temp);
            this->commtype.push_back(dev);
        }
        else if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (std::string str)
            {   return str == "name"; }   ))
        {

            found = temp.find_last_of(":");      
            temp = temp.substr(found+1); 
            temp.erase(temp.end()-1);
            this->name.push_back(temp);
        }
        
        else if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (std::string str)
            {   return str == "ID"; }   ))
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
    while(this->deviceNumber >= 0)
    {
        std::cout << this->devicetype[this->deviceNumber] << std::endl;
        std::cout << this->commtype[this->deviceNumber] << std::endl;
        std::cout << this->name[this->deviceNumber] << std::endl;
        std::cout << this->id[this->deviceNumber] << std::endl;
        this->deviceNumber--;
    }
}