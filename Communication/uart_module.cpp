#include "communication.hpp"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int Communication_c::Init_UART()
{
    vector<string> serial;
    serial.push_back("/dev/ttyUSB0");
    serial.push_back("/dev/ttyAMA0");
    serial.push_back("/dev/ttyS0");
    serial.push_back("/dev/ttyS1");

    /*if(!( init->numbOfDev ))
        return -1;
    */
    auto endOfDev = serial.end();
    for(auto it = serial.begin(); it != endOfDev; ++it)
    {
        const string temp = *it;
        SerialCom.serialport.uartFD = open(temp.c_str(),O_RDWR | O_NOCTTY | O_NDELAY );    /* code */
        if(SerialCom.serialport.uartFD > 0)   
            break;
    }
    
    if(SerialCom.serialport.uartFD < 0)
        {
            cout <<"Invalid Filedescriptor\n" \
                   "maybe don't connect any wire or privilage not proper?" \
                   "Try with sudo"<<endl;
    //        syslog(LOG_ERR,"%s",strerror(errno));
            return -1;
        }
    fcntl(SerialCom.serialport.uartFD,F_SETFL,O_RDWR);
    
    tcgetattr(SerialCom.serialport.uartFD,&SerialCom.serialport.old);
    SerialCom.serialport.term.c_cflag = CS8 | CLOCAL | CREAD ;
    SerialCom.serialport.term.c_iflag = IGNPAR;
    SerialCom.serialport.term.c_lflag &= ~( ICANON | ECHO | ISIG);
    SerialCom.serialport.term.c_oflag =0;
    SerialCom.serialport.term.c_cc[VTIME]=0;
    SerialCom.serialport.term.c_cc[VMIN]=0;
    cfsetispeed(&SerialCom.serialport.term,(speed_t)&SerialCom.serialport.BAUD);
    cfsetospeed(&SerialCom.serialport.term,(speed_t)&SerialCom.serialport.BAUD);

    tcflush(SerialCom.serialport.uartFD, TCIOFLUSH);
    if(!tcsetattr(SerialCom.serialport.uartFD,TCSANOW,&SerialCom.serialport.term))
        {
          
            cout <<"Serial port has succesfully initialized" << endl;
            //syslog(LOG_INFO,"Serial port OK");
            return 0;
        }
    else
        {
            //closeOnFAIL(init);
            
            //syslog(LOG_ERR,"%s %d",strerror(errno),SerialCom.serialport.uartFD);
            close(SerialCom.serialport.uartFD);
            return -1;
        }


}