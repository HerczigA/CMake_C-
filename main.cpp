#include <iostream>
#include "hdr/device.hpp"
#include "JSON/json.hpp"
#ifdef RPI_VERSION
    #include <wiringPi.h>
#endif
#include <stdlib.h>
#include <memory>
#include "main_Init/main_Init.hpp"
using namespace std;

int main(int argc, char *argv[])
{

    InitBase();
    const char* JSONpath ="./JSON/pattern/template.json";
    json_herczig::json JSONobj(*JSONpath);

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



    if(Vec_Actuators[0]->get_Name() == "ServoMotor")
    {

        while(true)
        {
            Vec_Sensors[0]->digital_Read_For_Button(Vec_Sensors[0]->get_Pin(0));
            if(Vec_Sensors[0]->buttonStateChanged())
            {

                Vec_Actuators[0]->pwmObj->pwm_Servo_Full_Limit(Vec_Actuators[0]->get_Pin(0), 500, Vec_Sensors[0]->getButtonState());
            }

        }
    }



#endif


    /*clock_t ticks1, ticks2;

	ticks1=clock();
	ticks2=ticks1;
	while((ticks2/CLOCKS_PER_SEC-ticks1/CLOCKS_PER_SEC)<1)
		ticks2=clock();

	printf("It took %ld ticks to wait one second.\n",ticks2-ticks1);
	printf("This value should be the same as CLOCKS_PER_SEC which is %d.\n",CLOCKS_PER_SEC);
	*/

    
    const uint8_t LCDPIN[] = {LCD_EN, LCD_RS, LCD_RW, LCD_D4, LCD_D5, LCD_D6, LCD_D7};
    uint8_t LCD_DATA_4[] = { LCD_D4, LCD_D5, LCD_D6, LCD_D7};
    uint8_t lcdstate = HIGH;
    const uint8_t dlen = 4;
    for (auto i = 0; i < 7; i++)
        pinMode(LCDPIN[i], OUTPUT);
        
    LCD_1602 lcd(LCD_EN, LCD_RS, LCD_RW, LCD_DATA_4, dlen);
    
    while (true)
    {
        
        lcd.DisplaySwtichOnOFF(lcdstate);
        lcdstate = !lcdstate;
        
    }
    



return 0;
}

