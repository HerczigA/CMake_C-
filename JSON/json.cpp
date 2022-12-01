#include <cstddef>
#include <regex>
#include <bits/stdc++.h>
#include "json.h"

using namespace std;
const char* const jsonPatternFile = "./JSON/pattern/template.json";

JsonComponent::JsonComponent(const string &p)
    : mJsonFile(p)
{
}

JsonComponent::JsonComponent()
    : mJsonFile(jsonPatternFile)
{

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
    if(!objects.is_null())
    {
        auto items = objects.items();
        for(auto& item : items)
        {
            Device tempdevice;
            cout << item.key() <<endl;
            cout << item.value() <<endl;

            for(auto& iter : item.value().items())
            {
                if(iter.key() == "commtype")
                {
                    string pattern= iter.value();
                    int value = getComType(pattern);
                    cout << "found one"<< pattern  << value << endl;
                }
                cout << "iter.key()" << iter.key() <<endl;
                cout << "iter.value()" << iter.value() <<endl;
            }
                
            
            // if(item.front() == "Sensor")
            //     cout << "Sensor" <<endl;
        }
    }
    
    
 
}

void JsonComponent::finishProcess()
{
    
}

JsonComponent::~JsonComponent()
{
    
}
