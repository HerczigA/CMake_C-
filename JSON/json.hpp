#ifndef JSON_HPP_INCLUDED
#define JSON_HPP_INCLUDED

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include "../hdr/device.hpp"


enum jsonerror_t
{
    E_JSON_OPEN = 51
};


namespace json_herczig
{

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

    class json
    {
            std::fstream fileHand;
            std::string jsonFile = "./JSON/pattern/template.json";
            devpatterns devPattern;
            compatterns comPattern;
            std::string lineFromFile;
            std::vector <std::string> pattern;
            std::vector <std::string> name;
            std::vector <int> devicetype;
            std::vector <int> commtype;
            std::vector <int> id;
            uint8_t deviceNumber;
            uint8_t Sensors = 0;
            uint8_t Actuators = 0;
            uint8_t SensorsAndActuators = 0;
            uint8_t regexmatcherForDevType(std::string &temp);
            uint8_t regexmatcherForComType(std::string &temp);

        public:
            json(const char &p);
            json();
            bool OpenPattern();
            void processPattern();
            void FinishProcess();
            
            Id_t getID(int element) { return id[0]; }
            devType_t getDevType(int element) { return devicetype[0]; }
            comm_t getComm(int element) { return commtype[0]; }
            std::string getName(int element) { return name[0]; }
            
            uint8_t getSensorsNumber() { return Sensors; }
            uint8_t getActuatorsNumber() { return Actuators; }
            uint8_t getSensorsActuatorsNumber() { return SensorsAndActuators; }
            ~json();
    };


}




#endif // JSON_HPP_INCLUDED
