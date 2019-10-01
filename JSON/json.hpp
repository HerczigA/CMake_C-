#ifndef _JSON_INCLUDED_HPP_
#define _JSON_INCLUDED_HPP_

#include <fstream>
#include <sstream>
#include <string>
#include "json.hpp"
#include <vector>
#include <iostream>


using namespace std;

enum json_objects
{

};


namespace json_herczig
{
    class json
    {
            fstream fileHand;
            const string jsonFile;
            string lineFromFile;
            vector<string> pattern;
            vector <string > name;
            vector <int> devicetype;
            vector <int> commtype;
            vector <int> id;
            uint8_t deviceNumber;
        
        public:
            json(const char &p): jsonFile(&p) {
                deviceNumber = 0;
            };
            void getPatternFileName();
            void getInfoFromPattern();
            void getLinesFromVector();
            void processPattern();
            void FinishProcess();

    };


}


#endif