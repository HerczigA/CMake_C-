#include <cstddef>
#include <regex>
#include <bits/stdc++.h>
#include "json.h"

using namespace std;
const char* const jsonPatternFile = "./JSON/pattern/template.json";

JsonComponent::JsonComponent(const string &p)
    : mJsonFile(p)
    , mDeviceNumber(0)
{
    
    mDirections.push_back("IN");
    mDirections.push_back("OUT");

}

JsonComponent::JsonComponent()
    : mJsonFile(jsonPatternFile)
    , mDeviceNumber(0)
{
    mDirections.push_back("IN");
    mDirections.push_back("OUT");
}

bool JsonComponent::openJson()
{
    if(mJsonFile == jsonPatternFile)
    {
        cout << "You use the pattern file from the repo. \n"
        << "Please be aware that it will not work just parsing the json for testing" <<endl;
        syslog(LOG_INFO, "Template json has been used");
    }

    mFileStream.open(mJsonFile, ios::in);
    try
    {
        if(mFileStream.is_open())
        {
            mJsonHandler = json::parse(mFileStream);
        }
    }
    catch(const exception& msg)
    {
        cout << "Exception under opening json file"<< endl;
        syslog(LOG_ERR,"Error occured while opening json for parsing:%s", msg.what());
        return false;
    }

    mFileStream.close();
    processing();
    // FinishProcess();
    
    return true;
}

uint8_t JsonComponent::getComType(string& communication)
{
    uint8_t result = comm_type::Unknown_communication;
    transform(communication.begin(), communication.end(), communication.begin(), ::tolower);
    auto it = CommType.find(communication);
    if(it != CommType.end())
        result = it->second;

    return result;
}

void JsonComponent::processing()
{
    size_t found;
    json objects = mJsonHandler["Devices"];
    set<string> devices = {"sensor", "actuator"};
    for(auto& item : objects)
    {
        cout << item <<endl;
        if(item.is_structured())
            cout << item["Sensor"] <<endl;
    }
    
    
    
    
    
    
    
//     while(mPattern.begin() != mPattern.end())
//     {

//         auto temp = mPattern[0];
//         auto tempEnd =temp.end();


//          if( std::string::npos !=temp.find("Device" ))
//         {
//             mPattern.erase(mPattern.begin());
//             temp = mPattern[0];
//             bool checkDevicetype = true;

//             for(; std::string::npos == temp.find("}" ); )
//             {
//                 if(checkDevicetype)
//                 {
//                     if(std::string::npos != temp.find("Sensor_Actuator"))
//                     {
//                         mSensorsAndActuators++;
//                         mDevicetype.push_back(SENSOR_ACTUATOR);
//                         checkDevicetype = false;
//                     }

//                     else if(std::string::npos != temp.find("Sensor"))
//                     {
//                         mSensors++;
//                         mDevicetype.push_back(SENSOR);
//                         checkDevicetype = false;
//                     }

//                     else if(std::string::npos != temp.find("Actuator"))
//                     {
//                         mActuators++;
//                         mDevicetype.push_back(ACTUATOR);
//                         checkDevicetype = false;
//                     }

//                     else if( tempEnd != std::find_if(temp.begin(),tempEnd,[] (char c)
//                     {  return (c == '{') || (c =='}') ; }   ))
//                         ;

//                     else
//                     {
//                         mDevicetype.push_back(Unknown_device);
//                     }
//                 }
//                 else
//                 {
//                     if( std::string::npos !=temp.find("commtype"))
//                     {
//                         size_t dev;
//                         dev = getComType(temp);
//                         mCommtype.push_back(dev);
//                     }
//                     else if( std::string::npos !=temp.find("name"))
//                     {

//                         found = temp.find_last_of(":");
//                         temp = temp.substr(found+1);
//                         temp.erase(0,2);
//                         temp.erase(temp.end()-2,temp.end()-0);
//                         mName.push_back(temp);
//                     }
//                     else if( std::string::npos !=temp.find("pin(s)"))
//                     {
//                         int pins = 1;
//                         found = temp.find_last_of(":");
//                         temp = temp.substr(found+1);
//                         if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (char c)
//                             {  return (c == '[' ); }   ))
//                         {
//                             pins = calculatePinNumbers(temp);
//                         }

//                         else
//                         {
//                             temp.erase(temp.begin()+1);
//                             mPinNumbers.push_back(atoi(temp.c_str()));
//                         }

//                         mPinOffset.push_back(pins);
//                     }
//                     else if( std::string::npos !=temp.find("dir"))
//                     {
//                         checkIO(temp);
//                     }
//                     else if( std::string::npos !=temp.find("ID"))
//                     {
//                         found = temp.find_last_of(":");
//                         temp = temp.substr(found+1);
//                         temp.erase(temp.begin()+1);
//                         mId.push_back(atoi(temp.c_str()));
//                         checkDevicetype = true;
//                     }
//                 }
//                 mPattern.erase(mPattern.begin());
//                 temp=mPattern[0];
//             }


//         }
//         mPattern.erase(mPattern.begin());
//     }

//     mDeviceNumber = mActuators + mSensors + mSensorsAndActuators;

// #if DEBUG
//     std::cout << "Device number: " <<(int) deviceNumber
//      << "\nActuator number:  " <<(int) mActuators
//      << "\nSensor number: " <<(int) Sensors
//      << "\nnSensor&Actuator number: " << (int)SensorsAndActuators<< std::endl;
//      for(auto it = pinNumbers.begin(); it != pinNumbers.end(); ++it)
//     {
//         std::cout << "pinNumbers: " <<*it << std::endl;
//     }
// #endif
}

void JsonComponent::finishProcess()
{
    
    Make_Device(getSensorsNumber(), Vec_Sensors, SENSOR);
    Make_Device(getActuatorsNumber(), Vec_Actuators, ACTUATOR);
    Make_Device(getSensorsActuatorsNumber(), Vec_SensActuators, SENSOR_ACTUATOR);

#if DEBUG_DEVICE
    std::cout << "Details about devices after read" << std::endl;
    size_t i = 0;
    while(i < deviceNumber)
    {

        std::cout << std::endl;
        std::cout << "ID: " << id[i] << std::endl;
        std::cout << "Name: " << (std::string)name[i] << std::endl;
        std::cout << "mDevicetype: " << mDevicetype[i] << std::endl;
        std::cout << "CommType: " << commtype[i] << std::endl;
        if(pinOffset[i])
        {
            std::cout << "pinOffset[i]: " << pinOffset[i] << std::endl;
            for(size_t j = 0; j < pinOffset[i]; j++)
            {
                std::cout << "Pins: " << pinNumbers[i+j] << std::endl;
            }
        }
        else
            std::cout << "Pins: " << pinNumbers[i] << std::endl;

        std::cout << std::endl;
        i++;
    }
#endif
}

JsonComponent::~JsonComponent()
{
    mName.clear();
    mDevicetype.clear();
    mCommtype.clear();
    mId.clear();

}
