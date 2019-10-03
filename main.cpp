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

    sensor Button("button",1,Actuator,Unknow_communication);
    
    actuator Motor("MicroServo",2,2,Bluetooth);
    cout << Button.get_ID() << endl;
    cout << Button.get_Name() << endl;

    cout << Motor.get_ID() << endl;
    cout << Motor.get_Name() << endl;

    vector<uint8_t> GPIO ={5};
    vector<uint8_t> inputpins = {4};
    uint8_t dir[] = {OUTPUT};
    uint8_t gpioNum = 1;
    int16_t DC = (argc > 1) ? atoi(argv[1]) : 0;
    time_ms_t waiting = (argv[2]) ? atoi(argv[2]) : DEF_SERVO_TIME;
    int buttonka = inputpins[0];

    cout << "start setpins()" << endl;
    if(!Button.setPins(inputpins,dir,gpioNum))
        cout << "yolo" << endl;

    bool loop = true;
    cout<<" GPIO size = " << sizeof(GPIO) << endl;
    
    while (loop)
    */
    const char* JSONpath ="./JSON/pattern/template.json";
    json_herczig::json JSONobj(*JSONpath);
 
        JSONobj.OpenPattern();
        JSONobj.processPattern();
//        JSONobj.FinishProcess();


    return 0;
}
