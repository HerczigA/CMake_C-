#ifndef _JSON_H_
#define _JSON_H_

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
    std::regex sensorPattern;
    std::regex actuatorPattern;
    std::regex sensorActuatorPattern;
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
            std::fstream fileHand;
            std::const string jsonFile;
            std::devpatterns devPattern;
            std::compatterns comPattern;
            std::string lineFromFile;
            std::vector<string> pattern;
            std::vector <std::string> name;
            std::vector <int> devicetype;
            std::vector <int> commtype;
            std::vector <int> id;
            uint8_t deviceNumber;
            uint8_t regexmatcherForDevType(std::string &temp);
            uint8_t regexmatcherForComType(std::string &temp);
                    
        public:
            json(const char &p): jsonFile{&p} {
                deviceNumber = 0;
                devPattern.actuatorPattern = std::regex(".*Actuat.*");
                devPattern.sensorPattern = std::regex(".*Sens.*");
                devPattern.sensorActuatorPattern = std::regex(".*sor_Actu.*");
                comPattern.SPIPattern = std::regex(".*SPI.*[a-zA-Z]");
                comPattern.I2CPattern = std::regex(".*I2C.*[a-zA-Z]");
                comPattern.UARTPattern = std::regex(".*UART.*[a-zA-Z]");
                comPattern.PWMPattern = std::regex(".*PWM.*[a-zA-Z]");
                comPattern.BluetoothPattern = std::regex(".*Bluetooth.*[a-zA-Z]");
            };
            void OpenPattern();
            void processPattern();
            void FinishProcess();

    };


}


#endif