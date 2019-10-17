#ifndef JSON_HPP_INCLUDED
#define JSON_HPP_INCLUDED

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <memory>
#include "../hdr/device.hpp"

#define DEBUG 0
#define MAX_DEV_TYPE 3

enum jsonerror_t
{
    E_JSON_OPEN = 51
};


namespace json_herczig
{

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
            compatterns comPattern;
            std::string lineFromFile;
            
            std::vector <std::string> pattern;
            std::vector <std::string> name;
            std::vector <int> devicetype;
            std::vector <int> commtype;
            std::vector <int> pinNumbers;
            std::vector <int> id;
            std::vector <int> pinOffset;
            

            uint8_t deviceNumber;
            uint8_t Sensors = 0;
            uint8_t Actuators = 0;
            uint8_t SensorsAndActuators = 0;
            uint8_t regexmatcherForComType(std::string &temp);

        public:
            json(const char &p);
            json();
            bool OpenPattern();
            void processPattern();
            void FinishProcess();
            
            Id_t getID(int element) { return id[element]; }
            devType_t getDevType(int element) { return devicetype[element]; }
            comm_t getComm(int element) { return commtype[element]; }
            std::string &getName(int element) { return name[element]; }
            uint8_t getPins(int element) { return pinNumbers[element]; }
            
            uint8_t getSensorsNumber() { return Sensors; }
            uint8_t getActuatorsNumber() { return Actuators; }
            uint8_t getSensorsActuatorsNumber() { return SensorsAndActuators; }
           
            template<typename getdevicesNumber, typename VectorOfDevice, typename type>
            void bridgeGetSet(getdevicesNumber a, std::vector<std::unique_ptr<VectorOfDevice>>& b, type c)
            {
                if(a)
                {
                    const int all = this->deviceNumber;
                    for(size_t i = 0; i < all; i++)
                    {
                        std::unique_ptr<VectorOfDevice> dev =std::make_unique<VectorOfDevice>();
                        if(devicetype[i] == c)
                        {
                            dev->device::setID(getID(i));
                            dev->device::setName(getName(i));
                            dev->device::setdevType(getDevType(i));
                            dev->device::setcommType(getComm(i));
                            if(pinOffset[i])
                            {
                                for(size_t j = 0; j < this->pinOffset[i]; j++)
                                    dev->device::setPinNumbers(getPins(i+j));
                            }
                            else
                                dev->device::setPinNumbers(getPins(i));

                            b.push_back(std::move(dev));
                        }   
                    }
                }
            }
            ~json();
    };


}




#endif // JSON_HPP_INCLUDED
