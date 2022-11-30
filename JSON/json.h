#pragma once

#include <regex>
#include <nlohmann/json.hpp>
#include "parameters.h"
#include "mainApp.h"
#include "device.h"
#include <map>

using json =  nlohmann::json;

class JsonComponent
{
    private:
        fstream mFileStream;
        json mJsonHandler; 
        string mJsonFile;
        vector <string> mPattern;
        vector <string> mName;
        vector <string> mDirections;
        vector <int> mDevicetype;
        vector <int> mCommtype;
        vector <int> mPinNumbers;
        vector <int> mId;
        vector <int> mPinOffset;
        vector <int> mDirectionsLevel;
        vector <int> mDirections_Offset;

        map<string, uint8_t> CommType{
            {"spi", comm_type::SPI},
            {"uart", comm_type::UART},
            {"i2c", comm_type::I2C},
            {"pwm", comm_type::PWM},
            {"bluetooth", comm_type::Bluetooth},
        };
        uint8_t mDeviceNumber;
        uint8_t mSensors = 0;
        uint8_t mActuators = 0;
        uint8_t mSensorsAndActuators = 0;
        uint8_t getComType(string &communication);


        Id_t getID(int element) { return mId[element]; }
        devType_t getDevType(int element) { return mDevicetype[element]; }
        comm_t getComm(int element) { return mCommtype[element]; }
        string &getName(int element) { return mName[element]; }
        uint8_t getPins(int element) { return mPinNumbers[element]; }
        uint8_t getDirs(int element) { return mDirectionsLevel[element]; }
        void processing();
        void finishProcess();


    public:
        JsonComponent(const string &p);
        JsonComponent();
        bool openJson();
        const uint8_t getSensorsNumber() const { return mSensors; }
        const uint8_t getActuatorsNumber() const { return mActuators; }
        const uint8_t getSensorsActuatorsNumber() const { return mSensorsAndActuators; }

        template<typename getdevicesNumber, typename VectorOfDevice, typename type>
        void Make_Device(getdevicesNumber a, vector<unique_ptr<VectorOfDevice>>& b, type c)
        {
            
            if(a)
            {
                int pin_Offset_Element = 0;
                int direction_Offset_Element = 0;
                const uint8_t all = mDeviceNumber;
                for(uint8_t i = 0; i < all; i++)
                {
                    unique_ptr<VectorOfDevice> dev =make_unique<VectorOfDevice>();
                    if(mDevicetype[i] == c)
                    {
                        dev->device::setID(getID(i));
                        dev->device::setName(getName(i));
                        dev->device::setdevType(getDevType(i));
                        dev->device::setcommType(getComm(i));

                        if(mDevicetype[i] == SENSOR_ACTUATOR)
                        {
                            for(uint8_t j = 0; j < mPinOffset[i]; j++)
                            {
                                dev->device::setPinsForuC(getPins(pin_Offset_Element+j),getDirs(direction_Offset_Element+j));
                            }
                            direction_Offset_Element += mDirections_Offset[i];
                            dev->device::setPins(dev->device::get_Pins());
                        }
                        else
                        {
                            for(uint8_t j = 0; j < mPinOffset[i]; j++)
                                dev->device::setPinNumbers(getPins(pin_Offset_Element+j));
                        }

                        b.push_back(move(dev));
                    }

                    pin_Offset_Element += mPinOffset[i];
                }
            }
        }
        ~JsonComponent();
};
