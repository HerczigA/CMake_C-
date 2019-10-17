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
    //vector<unique_ptr<actuator>> Actuators;
    const char* JSONpath ="./JSON/pattern/template.json";
    json_herczig::json JSONobj(*JSONpath);

    if(!JSONobj.OpenPattern())
        return E_JSON_OPEN;

    JSONobj.bridgeGetSet(JSONobj.getSensorsNumber(),Sensors,Sensor);
    JSONobj.bridgeGetSet(JSONobj.getActuatorsNumber(),Actuators,Actuator);
    //JSONobj.bridgeGetSet(JSONobj.getSensorsNumber(),Se);

#if DEBUG
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
            cout<< "Pins: " <<(int) Sensors[i]->get_Pins(j) << endl;
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
            cout<< "Pins: " <<(int) Actuators[i]->get_Pins(j) << endl;
            j++;
        }
    }

#endif
    uint8_t dir[] = {OUTPUT};
    uint8_t dir2[] = {INPUT};
    uint8_t gpioNum = 1;
    if(Actuators[0]->get_Name() == "ServoMotor")
    {
        vector<uint8_t> pinek;
        vector<uint8_t> senspinek;
        pinek.push_back(Actuators[0]->get_Pins(0));
        senspinek.push_back(Sensors[0]->get_Pins(0));
        Actuators[0]->setPins(pinek, dir, gpioNum);
        Sensors[0]->setPins(senspinek, dir2, gpioNum);
        
        Actuators[0]->pwm_ServoSetup(pinek, gpioNum);
        //Actuators[0]->pwm_Servo_Full_Limit(pinek[0],500);

        while(true)
        {
            Sensors[0]->digital_Read(Sensors[0]->get_Pins(0));
            if(Sensors[0]->buttonStateChanged())
            {
                
                Actuators[0]->pwm_Servo_Full_Limit(pinek[0], 500, Sensors[0]->getButtonState());
            }
                
        }
    }
    
    
    
    return 0;
}
