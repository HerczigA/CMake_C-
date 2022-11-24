#include "mainApp.h"
using namespace std;

int main(int argc, char *argv[])
{

    MainApp mainApp();
    const char* JSONpath ="./JSON/pattern/template.json";
    json JSONobj(*JSONpath);

    if(!JSONobj.OpenPattern())
        return E_JSON_OPEN;


#if DEBUG_DEVICE
    cout << "\nSENSORS DETAILS " << endl;
    for(size_t i = 0; i < JSONobj.getSensorsNumber(); i++)
    {
        size_t j = 0;
        cout<< "ID: " << Vec_Sensors[i]->get_ID() << endl;
        cout<< "Name: " << Vec_Sensors[i]->get_Name() << endl;
        cout<< "DevType: "  << (int) Vec_Sensors[i]->get_Dev_Type() << endl;
        cout<< "CommType: " <<(int) Vec_Sensors[i]->get_Comm_Type() << endl;
        for(auto it = 0; it < Vec_Sensors[i]->get_PinNumbers(); it++)
        {
            cout<< "Pins: " <<(int) Vec_Sensors[i]->get_Pin(j) << endl;
            j++;
        }

    }
    cout << "\nACTUATORS DETAILS " << endl;
    for(size_t i = 0; i < JSONobj.getActuatorsNumber(); i++)
    {
        size_t j = 0;
        cout<< "ID: " << Vec_Actuators[i]->get_ID() << endl;
        cout<< "Name: " << Vec_Actuators[i]->get_Name() << endl;
        cout<< "DevType: "  << (int) Vec_Actuators[i]->get_Dev_Type() << endl;
        cout<< "CommType: " <<(int) Vec_Actuators[i]->get_Comm_Type() << endl;
        for(auto it = 0; it < Vec_Actuators[i]->get_PinNumbers(); it++)
        {
            cout<< "Pins: " <<(int) Vec_Actuators[i]->get_Pin(j) << endl;
            j++;
        }
    }
    cout << "\nuC DETAILS " << endl;
    for(size_t i = 0; i < JSONobj.getSensorsActuatorsNumber(); i++)
    {
        size_t j = 0;
        cout<< "ID: " << Vec_SensActuators[i]->get_ID() << endl;
        cout<< "Name: " << Vec_SensActuators[i]->get_Name() << endl;
        cout<< "DevType: "  << (int) Vec_SensActuators[i]->get_Dev_Type() << endl;
        cout<< "CommType: " <<(int) Vec_SensActuators[i]->get_Comm_Type() << endl;
        for(auto it = 0; it < Vec_SensActuators[i]->get_PinNumbers(); it++)
        {
            cout<< "Pins: " <<(int) Vec_SensActuators[i]->get_Pin(j) << endl;
            cout<< "And Directions: " <<(int) Vec_SensActuators[i]->get_Dirs(j) << endl;
            j++;
        }

    }

#endif

    if(Vec_Actuators[0]->get_Name() == "ServoMotor")
    {

        while(true)
        {
            Vec_Sensors[0]->digital_Read(Vec_Sensors[0]->get_Pin(0));
            // if(Vec_Sensors[0]->buttonStateChanged())
            // {

            //     Vec_Actuators[0]->pwm_Servo_Full_Limit(Vec_Actuators[0]->get_Pin(0), 500, Vec_Sensors[0]->getButtonState());
            // }

        }
    }



    return 0;
}
