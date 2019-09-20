#include <iostream>
#include "hdr/test.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        filehandler fh(*argv[1]);
        fh.getPatternFileName();
        fh.getInfoFromPattern();
        fh.getLinesFromVector();
        fh.processPattern();
        fh.FinishProcess();
    }

    sensor senDev("IRALED",0,5);
    actuator Motor("MicroServo",0,2);
    cout << senDev.getID() << endl; 
    cout << senDev.getName() << endl;
    cout << senDev.getType() << endl;  
    
    cout << Motor.getID() << endl; 
    cout << Motor.getName() << endl;
    cout << Motor.getType() << endl;  

    uint8_t GPIO[] ={1};
    uint8_t dir[] = {OUTPUT};
    uint8_t gpioNum = 1;
  /*  if(!senDev.setPins(GPIO,dir,gpioNum))
        cout << "yolo" << endl;
*/
    if(!Motor.pwm_Setup(GPIO,gpioNum))
        cout << "yolo" << endl;

    for(;;)
    {
        for(auto i = 0; i <MAX_DC; i++)
            Motor.pwm_Write(GPIO[0],i,10);
        for(auto j = MAX_DC -1; j != 0; j--)
            Motor.pwm_Write(GPIO[0],j,10);
    }

    return 0;
}