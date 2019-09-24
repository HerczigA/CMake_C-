#include <iostream>
#include "hdr/device.hpp"
#include <wiringPi.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
    /*if(argc > 1)
    {
        filehandler fh(*argv[1]);
        fh.getPatternFileName();
        fh.getInfoFromPattern();
        fh.getLinesFromVector();
        fh.processPattern();
        fh.FinishProcess();
    }*/

    sensor senDev("IRALED",3,5,SPI);
    actuator Motor("MicroServo",2,2,Wifi);
    cout << senDev.get_ID() << endl;
    cout << senDev.get_Name() << endl;

    cout << Motor.get_ID() << endl;
    cout << Motor.get_Name() << endl;

    vector<uint8_t> GPIO ={5};
    uint8_t dir[] = {OUTPUT};
    uint8_t gpioNum = 1;
    int16_t DC = (argc > 1) ? atoi(argv[1]) : 0;
    time_ms_t waiting = (*argv[2]) ? atoi(argv[2]) : 500;

    if(!senDev.setPins(GPIO,dir,gpioNum))
        cout << "yolo" << endl;

    bool loop = false;
    cout<<" GPIO size = " << sizeof(GPIO) << endl;
    Motor.pwm_Setup(GPIO,gpioNum);
    Motor.pwm_Servo_Write_In_Loop(GPIO[0],DC,waiting,loop);

    


    return 0;
}
