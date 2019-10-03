#ifndef JSON_HPP_INCLUDED
#define JSON_HPP_INCLUDED

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <regex>


enum json_objects
{

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
            std::string jsonFile;
            devpatterns devPattern;
            compatterns comPattern;
            std::string lineFromFile;
            std::vector <std::string> pattern;
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
                comPattern.SPIPattern = std::regex("(SPI)|(spi)]");
                comPattern.I2CPattern = std::regex("(I2C)|(i2c)");
                comPattern.UARTPattern = std::regex("(UART)|(uart)");
                comPattern.PWMPattern = std::regex("(pwm)|(PWM)");
                comPattern.BluetoothPattern = std::regex("Bluetooth");
            };
            void OpenPattern();
            void processPattern();
            void FinishProcess();

    };


}




#endif // JSON_HPP_INCLUDED
