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
   
    vector<sensor> Sensors;   // vector<device*> Devices;
    const char* JSONpath ="./JSON/pattern/template.json";

    if(!JSONobj.OpenPattern())
        return E_JSON_OPEN;

    if(JSONobj.getSensorsNumber())
    {
        size_t i = JSONobj.getSensorsNumber();
        for(;i > 0; --i)
        Sensors.push_back

    }
        /*unique_ptr<sensor> s1(new sensor);
        s1->setName(stringtempike);
        s1->setID(tempike);
        s1->setdevType(tempike);
        s1->setcommType(tempike);*/
    
    return 0;
}
