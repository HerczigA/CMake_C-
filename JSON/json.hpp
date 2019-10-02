#ifndef _JSON_INCLUDED_HPP_
#define _JSON_INCLUDED_HPP_

#include <fstream>
#include <sstream>
#include <string>
#include "json.hpp"
#include <vector>
#include <iostream>
#include <regex>


enum json_objects
{

};

struct devpatterns
{
    std::regex sensorPattern;        //(".*Sens.*");
    std::regex actuatorPattern;      //(".*Actuat.*");
    std::regex sensorActuatorPattern;//(".*sor_Actu.*");
};

struct compatterns
{
    std::regex SPIPattern;
    std::regex I2CPattern;
    std::regex UARTPattern;
    std::regex PWMPattern;
    std::regex BluetoothPattern;

};

namespace json_herczig
{
    class json
    {
            fstream fileHand;
            const string jsonFile;
            devpatterns devPattern;
            compatterns comPattern;
            string lineFromFile;
            vector<string> pattern;
            vector <string > name;
            vector <int> devicetype;
            vector <int> commtype;
            vector <int> id;
            uint8_t deviceNumber;
            uint8_t regexmatcherForDevType(std::string &temp);
            uint8_t regexmatcherForComType(std::string &temp);
                    
        public:
            json(const char &p): jsonFile(&p) {
                deviceNumber = 0;
                devPattern.actuatorPattern(".*Actuat.*");
                devPattern.sensorPattern(".*Sens.*");
                devPattern.sensorActuatorPattern(".*sor_Actu.*");
                comPattern.SPIPattern(".*SPI.*[a-zA-Z]");
                comPattern.I2CPattern(".*I2C.*[a-zA-Z]");
                comPattern.UARTPattern(".*UART.*[a-zA-Z]");
                comPattern.PWMPattern(".*PWM.*[a-zA-Z]");
                comPattern.BluetoothPattern(".*Bluetooth.*[a-zA-Z]");
            };
            void OpenPattern();
            void processPattern();
            void FinishProcess();

    };


}


#endif