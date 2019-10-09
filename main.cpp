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
    const char* JSONpath ="./JSON/pattern/template.json";

    if(!JSONobj.OpenPattern())
        return E_JSON_OPEN;

    
    if(JSONobj.getSensorsNumber())
    {
        for(size_t i = 0; i < JSONobj.getSensorsNumber(); i++)
        {
            unique_ptr<sensor> dev = make_unique<sensor>();
            dev->setID(JSONobj.getID(i));
            dev->setName(JSONobj.getName(i));
            dev->setdevType(JSONobj.getDevType(i));
            dev->setcommType(JSONobj.getComm(i));
            Sensors.push_back(move(dev));
        }
        

    }
#if !DEBUG
    for(size_t i = 0; i < JSONobj.getSensorsNumber(); i++)
    {
        cout<< "ID: " << Sensors[i]->get_ID() << endl;
        cout<< "Name: " << Sensors[i]->get_Name() << endl;
        cout<< "DevType: "  << (int) Sensors[i]->get_Dev_Type() << endl;
        cout<< "CommType: " <<(int) Sensors[i]->get_Comm_Type() << endl;
#endif

    }
    
    return 0;
}
