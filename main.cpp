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
        size_t j = 0;
        cout<< "ID: " << Sensors[i]->get_ID() << endl;
        cout<< "Name: " << Sensors[i]->get_Name() << endl;
        cout<< "DevType: "  << (int) Sensors[i]->get_Dev_Type() << endl;
        cout<< "CommType: " <<(int) Sensors[i]->get_Comm_Type() << endl;
        for(auto it = 0; it < Sensors[i]->get_PinNumbers(); it++)
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
    }
    vector<device*> Devices;

    JSONobj.OpenPattern();
    JSONobj.processPattern();
    JSONobj.FinishProcess();
    
    
        unique_ptr<sensor> s1(new sensor);
        s1->setName(JSONobj.getName(0));
        s1->setID(JSONobj.getID(0));
        s1->setdevType(JSONobj.getDevType(0));
        s1->setcommType(JSONobj.getCommType(0));
    
    return 0;
}
