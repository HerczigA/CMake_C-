#include <iostream>
#include "hdr/test.hpp"
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

    sensor senDev("IRALED",0,5);
    actuator Motor("MicroServo",0,2);
    cout << senDev.getID() << endl;
    cout << senDev.getName() << endl;
    cout << senDev.getType() << endl;

    cout << Motor.getID() << endl;
    cout << Motor.getName() << endl;
    cout << Motor.getType() << endl;

    vector<uint8_t> GPIO ={5};
    //uint8_t dir[] = {OUTPUT};
    uint8_t gpioNum = 1;
    int16_t DC = (argc > 1) ? atoi(argv[1]) : 0;
    /*  if(!senDev.setPins(GPIO,dir,gpioNum))
        cout << "yolo" << endl;
    */
    cout<<" GPIO size = " << sizeof(GPIO) << endl;
    if(!Motor.pwm_Setup(GPIO,gpioNum))
    {
        cout << "yolo" << endl;
        Motor.pwm_Servo_Write(GPIO[0],DC,1000);
    }


    return 0;
}
