#pragma once 

#include <iterator>
#include <bits/stdc++.h>
#include "parameters.h"
#include "device.h"
#include "json.h"
#include <nlohmann/json.hpp>

extern vector<unique_ptr<sensor>> Vec_Sensors;
extern vector<unique_ptr<actuator>> Vec_Actuators;
extern vector<unique_ptr<actuator>> Vec_SensActuators;

class JsonComponent;

using namespace std;


class MainApp{
    public:
        MainApp(const string& configFile);
        MainApp();

    private:
        string mConfig;
        unique_ptr<JsonComponent> mJson;
};
