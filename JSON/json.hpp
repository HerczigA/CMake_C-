#ifndef _JSON_INCLUDED_HPP_
#define _JSON_INCLUDED_HPP_

#include <fstream>
#include <sstream>
#include <string>
#include "json.hpp"
#include <vector>
#include <iostream>
#include <regex>

using namespace std;

enum json_objects
{

};

struct devpatterns
{
    regex sensorPattern;        //(".*Sens.*");
    regex actuatorPattern;      //(".*Actuat.*");
    regex sensorActuatorPattern;//(".*sor_Actu.*");
};

struct compatterns
{
    regex SPIPattern;
    regex I2CPattern;
    regex UARTPattern;
    regex PWMPattern;
    regex BluetoothPattern;

}

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
                comPattern.PWMattern(".*PWM.*[a-zA-Z]");
                comPattern.BluetoothPattern(".*Bluetooth.*[a-zA-Z]");
            };
            void OpenPattern();
            void processPattern();
            void FinishProcess();

    };


}


#endif