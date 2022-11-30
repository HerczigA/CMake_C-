#include "communication.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int Communication::Init_UART()
{
    vector<string> serial;
    serial.push_back("/dev/ttyUSB0");
    serial.push_back("/dev/ttyAMA0");
    serial.push_back("/dev/ttyS0");
    serial.push_back("/dev/ttyS1");

    
    auto endOfDev = serial.end();
    for(auto it = serial.begin(); it != endOfDev; ++it)
    {
        const string temp = *it;
        mSerialCom.serialport.uartFD = open(temp.c_str(),O_RDWR | O_NOCTTY | O_NDELAY );    /* code */
        if(mSerialCom.serialport.uartFD > 0)   
            break;
    }
    
    if(mSerialCom.serialport.uartFD < 0)
        {
            cout <<"Invalid Filedescriptor\n" \
                   "maybe don't connect any wire or privilage not proper?" \
                   "Try with sudo"<<endl;
            syslog(LOG_ERR,"%s",strerror(errno));
            return -1;
        }
    fcntl(mSerialCom.serialport.uartFD,F_SETFL,O_RDWR);
    
    tcgetattr(mSerialCom.serialport.uartFD,&mSerialCom.serialport.oldTermios);
    mSerialCom.serialport.term.c_cflag = CS8 | CLOCAL | CREAD ;
    mSerialCom.serialport.term.c_iflag = IGNPAR;
    mSerialCom.serialport.term.c_lflag &= ~( ICANON | ECHO | ISIG);
    mSerialCom.serialport.term.c_oflag =0;
    mSerialCom.serialport.term.c_cc[VTIME]=0;
    mSerialCom.serialport.term.c_cc[VMIN]=0;
    cfsetispeed(&mSerialCom.serialport.term, mSerialCom.serialport.BAUD);
    cfsetospeed(&mSerialCom.serialport.term, mSerialCom.serialport.BAUD);

    tcflush(mSerialCom.serialport.uartFD, TCIOFLUSH);
    if(!tcsetattr(mSerialCom.serialport.uartFD,TCSANOW,&mSerialCom.serialport.term))
        {
          
            cout <<"Serial port has succesfully initialized" << endl;
            //syslog(LOG_INFO,"Serial port OK");
            return 0;
        }
    else
        {
            //closeOnFAIL(init);
            
            //syslog(LOG_ERR,"%s %d",strerror(errno),mSerialCom.serialport.uartFD);
            close(mSerialCom.serialport.uartFD);
            return -1;
        }


}