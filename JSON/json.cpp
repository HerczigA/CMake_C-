#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <regex>
#include <stdlib.h>#include "json.hpp"



void json_herczig::json::getPatternFileName()
{
    cout << jsonFile << endl;
}

void json_herczig::json::getInfoFromPattern()
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

void json_herczig::json::getLinesFromVector()
{
    for(auto x : pattern)
        cout << x << endl;
}

uint8_t json_herczig::json::regexmatcherForDevType(std::string& temp)
{
    uint8_t result;
    if(regex_match(temp, this->devPattern.sensorPattern))
        result = 1;
    
    else if(regex_match(temp, this->devPattern.actuatorPattern))
        result = 2;
    
    else if(regex_match(temp, this->devPattern.sensorActuatorPattern))  
        result = 3;
    
    else
        result = 4;
        
    return result;
}

uint8_t json_herczig::json::regexmatcherForComType(std::string& temp)
{
    uint8_t result = 0;
    if(regex_match(temp, this->comPattern.SPIPattern))
        result = 1;
    
    else if(regex_match(temp, this->comPattern.I2CPattern))
        result = 2;
    
    else if(regex_match(temp, this->comPattern.UARTPattern))  
        result = 3;
    
    else if(regex_match(temp, this->comPattern.PWMPattern))  
        result = 4;

    else if(regex_match(temp, this->comPattern.BluetoohPattern))  
        result = 5;
    
    else
        result = 6;
}


void json_herczig::json::processPattern()
{
  
    size_t found;
    auto it = pattern.begin();
    while(it != pattern.end())
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

        it++;  
    }
    

}


void json_herczig::json::FinishProcess()
{
    try
    {
        fileHand.open(newFile.c_str(),ios::out);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << e.what() << '\n';
        return;
    }

    fileHand << pattern[0];

    fileHand.close();
}