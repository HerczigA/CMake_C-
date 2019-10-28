#include <iostream>
#include "hdr/device.hpp"
#include "JSON/json.hpp"
#include <wiringPi.h>
#include <stdlib.h>
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{

    vector<unique_ptr<sensor>> Sensors;
    vector<unique_ptr<actuator>> Actuators;
    vector<unique_ptr<actuator>> SensActuators;
    const char* JSONpath ="./JSON/pattern/template.json";
    json_herczig::json JSONobj(*JSONpath);

    if(!JSONobj.OpenPattern())
        return E_JSON_OPEN;

    JSONobj.Make_Device(JSONobj.getSensorsNumber(),Sensors, Sensor);
    JSONobj.Make_Device(JSONobj.getActuatorsNumber(),Actuators, Actuator);
    JSONobj.Make_Device(JSONobj.getSensorsActuatorsNumber(),SensActuators, Sensor_Actuator);

#if 1
    cout << "\nSENSORS DETAILS " << endl;
    for(size_t i = 0; i < JSONobj.getSensorsNumber(); i++)
    {
        size_t j = 0;
        cout<< "ID: " << Sensors[i]->get_ID() << endl;
        cout<< "Name: " << Sensors[i]->get_Name() << endl;
        cout<< "DevType: "  << (int) Sensors[i]->get_Dev_Type() << endl;
        cout<< "CommType: " <<(int) Sensors[i]->get_Comm_Type() << endl;
        for(auto it = 0; it < Sensors[i]->get_PinNumbers(); it++)
        {
            cout<< "Pins: " <<(int) Sensors[i]->get_Pin(j) << endl;
            j++;
        }

    }
    cout << "\nACTUATORS DETAILS " << endl;
    for(size_t i = 0; i < JSONobj.getActuatorsNumber(); i++)
    {
        size_t j = 0;
        cout<< "ID: " << Actuators[i]->get_ID() << endl;
        cout<< "Name: " << Actuators[i]->get_Name() << endl;
        cout<< "DevType: "  << (int) Actuators[i]->get_Dev_Type() << endl;
        cout<< "CommType: " <<(int) Actuators[i]->get_Comm_Type() << endl;
        for(auto it = 0; it < Actuators[i]->get_PinNumbers(); it++)
        {
            cout<< "Pins: " <<(int) Actuators[i]->get_Pin(j) << endl;
            j++;
        }
    }
    cout << "\nuC DETAILS " << endl;
    for(size_t i = 0; i < JSONobj.getSensorsActuatorsNumber(); i++)
    {
        size_t j = 0;
        cout<< "ID: " << SensActuators[i]->get_ID() << endl;
        cout<< "Name: " << SensActuators[i]->get_Name() << endl;
        cout<< "DevType: "  << (int) SensActuators[i]->get_Dev_Type() << endl;
        cout<< "CommType: " <<(int) SensActuators[i]->get_Comm_Type() << endl;
        for(auto it = 0; it < SensActuators[i]->get_PinNumbers(); it++)
        {
            cout<< "Pins: " <<(int) SensActuators[i]->get_Pin(j) << endl;
            cout<< "And Directions: " <<(int) SensActuators[i]->get_Dirs(j) << endl;
            j++;
        }

    }

#endif

    //uint8_t gpioNum = 1;
    if(Actuators[0]->get_Name() == "ServoMotor")
    {

        while(true)
        {
            Sensors[0]->digital_Read(Sensors[0]->get_Pin(0));
            if(Sensors[0]->buttonStateChanged())
            {

                Actuators[0]->pwm_Servo_Full_Limit(Actuators[0]->get_Pin(0), 500, Sensors[0]->getButtonState());
            }

        }
    }



    return 0;
}
