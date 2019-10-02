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
    regex sensorPattern;//(".*Sens.*");
    regex actuatorPattern;//(".*Actuat.*");
    regex sensorActuatorPattern;//(".*sor_Actu.*");
};

namespace json_herczig
{
    class json
    {
            fstream fileHand;
            const string jsonFile;
            devpatterns devPattern;
            string lineFromFile;
            vector<string> pattern;
            vector <string > name;
            vector <int> devicetype;
            vector <int> commtype;
            vector <int> id;
            uint8_t deviceNumber;
            uint8_t regexmatcherForDevType(std::string &temp);
            uint8_t regexmatcherForComType(std::string &temp);
            uint8_t regexmatcherForIDType(std::string &temp);
        
        public:
            json(const char &p): jsonFile(&p) {
                deviceNumber = 0;
                devPattern.actuatorPattern(".*Actuat.*");
                devPattern.sensorPattern(".*Sens.*");
                devPattern.sensorActuatorPattern(".*sor_Actu.*");
            };
            void getPatternFileName();
            void getInfoFromPattern();
            void getLinesFromVector();
            void processPattern();
            void FinishProcess();

    };


}


#endif