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

    cout << senDev.getID() << endl; 
    cout << senDev.getName() << endl;
    cout << senDev.getType() << endl;  
    
    uint8_t GPIO[] ={0,1};
    bool dir[] = {true, false};

    if(!senDev.setPins(GPIO,dir,2))
        cout << "yolo" << endl;
    return 0;
}