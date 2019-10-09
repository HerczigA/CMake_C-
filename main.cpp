#include <iostream>
#include "hdr/device.hpp"
#include "JSON/json.hpp"
#include <wiringPi.h>
#include <stdlib.h>
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{
        {
            cout<< "Pins: " <<(int) Sensors[i]->get_Pins(j) << endl;
            j++;
        }
    for(size_t i = 0; i < JSONobj.getActuatorsNumber(); i++)
    {
        size_t j = 0;
        cout<< "ID: " << Actuators[i]->get_ID() << endl;
        cout<< "Name: " << Actuators[i]->get_Name() << endl;
        cout<< "DevType: "  << (int) Actuators[i]->get_Dev_Type() << endl;
        cout<< "CommType: " <<(int) Actuators[i]->get_Comm_Type() << endl;
        for(auto it = 0; it < Actuators[i]->get_PinNumbers(); it++)
        {
            cout<< "Pins: " <<(int) Actuators[i]->get_Pins(j) << endl;
            j++;
        }
   
    vector<unique_ptr<sensor>> Sensors;
    vector<unique_ptr<actuator>> Actuators;
    const char* JSONpath ="./JSON/pattern/template.json";

    if(!JSONobj.OpenPattern())
        return E_JSON_OPEN;

    JSONobj.bridgeGetSet(JSONobj.getSensorsNumber(),Sensors,Sensor);
    JSONobj.bridgeGetSet(JSONobj.getActuatorsNumber(),Actuators,Actuator);
    //JSONobj.bridgeGetSet(JSONobj.getSensorsNumber(),Sensors);

#if DEBUG
    cout << "\nSENSORS DETAILS " << endl; 
    for(size_t i = 0; i < JSONobj.getSensorsNumber(); i++)
    {
        cout<< "ID: " << Sensors[i]->get_ID() << endl;
        cout<< "Name: " << Sensors[i]->get_Name() << endl;
        cout<< "DevType: "  << (int) Sensors[i]->get_Dev_Type() << endl;
        cout<< "CommType: " <<(int) Sensors[i]->get_Comm_Type() << endl;
    }
    cout << "\nACTUATORS DETAILS " << endl;
    for(size_t i = 0; i < JSONobj.getActuatorsNumber(); i++)
    {
        cout<< "ID: " << Actuators[i]->get_ID() << endl;
        cout<< "Name: " << Actuators[i]->get_Name() << endl;
        cout<< "DevType: "  << (int) Actuators[i]->get_Dev_Type() << endl;
        cout<< "CommType: " <<(int) Actuators[i]->get_Comm_Type() << endl;
    }
#endif

    
    
    return 0;
}
