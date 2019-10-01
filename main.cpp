#include <iostream>
#include "hdr/device.hpp"
#include "JSON/json.hpp"
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
    }

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
    time_ms_t waiting = (argv[2]) ? atoi(argv[2]) : DEF_SERVO_TIME;

    cout << "start setpins()" << endl;
    if(!senDev.setPins(GPIO,dir,gpioNum))
        cout << "yolo" << endl;

    bool loop = false;
    cout<<" GPIO size = " << sizeof(GPIO) << endl;
    Motor.pwm_Setup(GPIO,gpioNum);
    Motor.pwm_Servo_Full_Limit(GPIO[0],waiting);
    */
    const char* JSONpath ="JSON/pattern/template.json";
    json_herczig::json JSONobj(*JSONpath);
        JSONobj.getPatternFileName();
        JSONobj.getInfoFromPattern();
        JSONobj.getLinesFromVector();
        JSONobj.processPattern();
        JSONobj.FinishProcess();


    return 0;
}
