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
        
        map<string, uint8_t> CommType{
            {"spi", comm_type::SPI},
            {"uart", comm_type::UART},
            {"i2c", comm_type::I2C},
            {"pwm", comm_type::PWM},
            {"bluetooth", comm_type::Bluetooth},
        };
        set<string> mDirections{"IN", "OUT"};
        set<string> mDeviceKeyWords{"type", "comtype", "name", "pins", "direction(s)"};
        set<string> mDatabaseKeyWords{"type", "host", "dbName", "user", "password"};
        uint8_t getComType(string &communication);


        void processing();
        void finishProcess();


    public:
        JsonComponent(const string &p);
        JsonComponent();
        bool openJson();
        
        
        ~JsonComponent();
};
