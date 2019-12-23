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
#include "../main_Init/main_Init.hpp"
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
            std::vector <std::string> DIRS;
            std::vector <int> devicetype;
            std::vector <int> commtype;
            std::vector <int> pinNumbers;
            std::vector <int> id;
            std::vector <int> pinOffset;
            std::vector <int> directions;
            std::vector <int> directions_Offset;


            uint8_t deviceNumber;
            uint8_t Sensors = 0;
            uint8_t Actuators = 0;
            uint8_t SensorsAndActuators = 0;
            uint8_t regexmatcherForComType(std::string &temp);


            Id_t getID(int element) { return id[element]; }
            devType_t getDevType(int element) { return devicetype[element]; }
            comm_t getComm(int element) { return commtype[element]; }
            std::string &getName(int element) { return name[element]; }
            uint8_t getPins(int element) { return pinNumbers[element]; }
            uint8_t getDirs(int element) { return directions[element]; }
            


        public:
            json(const char &p);
            json();
            bool OpenPattern();
            void processPattern();
            void FinishProcess();
            int calculatePinNumbers(std::string &text);
            void checkIO(std::string &text);
            uint8_t getSensorsNumber() const { return Sensors; }
            uint8_t getActuatorsNumber() const { return Actuators; }
            uint8_t getSensorsActuatorsNumber() const { return SensorsAndActuators; }

            template<typename getdevicesNumber, typename VectorOfDevice, typename type>
            void Make_Device(getdevicesNumber a, std::vector<std::unique_ptr<VectorOfDevice>>& b, type c)
            {
                
                if(a)
                {
                    int pin_Offset_Element = 0;
                    int direction_Offset_Element = 0;
                    const uint8_t all = deviceNumber;
                    for(uint8_t i = 0; i < all; i++)
                    {
                        std::unique_ptr<VectorOfDevice> dev =std::make_unique<VectorOfDevice>();
                        if(devicetype[i] == c)
                        {
                            dev->device::setID(getID(i));
                            dev->device::setName(getName(i));
                            dev->device::setdevType(getDevType(i));
                            dev->device::setcommType(getComm(i));

                            if(devicetype[i] == SENSOR_ACTUATOR)
                            {
                                for(uint8_t j = 0; j < pinOffset[i]; j++)
                                {
                                    dev->device::setPinsForuC(getPins(pin_Offset_Element+j),getDirs(direction_Offset_Element+j));
                                }
                                direction_Offset_Element += directions_Offset[i];
                                dev->device::setPins(dev->device::get_Pins());
                            }
                            else
                            {
                                for(uint8_t j = 0; j < pinOffset[i]; j++)
                                    dev->device::setPinNumbers(getPins(pin_Offset_Element+j));
                            }

                            b.push_back(std::move(dev));
                        }

                        pin_Offset_Element += pinOffset[i];
                    }
                }
            }
            ~json();
    };


}




#endif // JSON_HPP_INCLUDED
