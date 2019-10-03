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