#include "communication.h"
#include <string>
#include <iostream>
#include <vector>

void Serial_UART::setBaud(const int& baud)
{
    mBAUD = baud;
}

com_error_t Serial_UART::initCommunication()
{
    com_error_t result = E_OK;
    set<string> serialPathes;
    serialPathes.insert("/dev/ttyUSB0");
    serialPathes.insert("/dev/ttyAMA0");
    serialPathes.insert("/dev/ttyS0");
    serialPathes.insert("/dev/ttyS1");

    
    
    for(auto path = serialPathes.begin(); path != serialPathes.end(); path++)
    {
        mFd = open(path->c_str(), O_RDWR | O_NOCTTY | O_NDELAY );    /* code */
        if(mFd > 0)   
            break;
    }
    
    if(mFd < 0)
    {
        result = E_FD_NOK;
        cout <<"Invalid Filedescriptor\n" \
                "maybe don't connect any wire or privilage not proper?" \
                "Try with sudo"<<endl;
        syslog(LOG_ERR,"%s",strerror(errno));
        return result;
    }
    fcntl(mFd,F_SETFL,O_RDWR);
    
    tcgetattr(mFd, &mOldTermios);
    mTerm.c_cflag = CS8 | CLOCAL | CREAD ;
    mTerm.c_iflag = IGNPAR;
    mTerm.c_lflag &= ~( ICANON | ECHO | ISIG);
    mTerm.c_oflag =0;
    mTerm.c_cc[VTIME]=0;
    mTerm.c_cc[VMIN]=0;
    cfsetispeed(&mTerm, mBAUD);
    cfsetospeed(&mTerm, mBAUD);

    tcflush(mFd, TCIOFLUSH);
    if(!tcsetattr(mFd, TCSANOW, &mTerm))
    {
        
        cout <<"Uart (serial) port OK" << endl;
        syslog(LOG_INFO,"Uart (serial) port has succesfully initialized");
    }
    else
    {
        result = E_UART_SETUP_NOK;
        closeOnFAIL();
        cout << "Could not setup uart with tcsetattr()" << endl;
        syslog(LOG_ERR,"%s",strerror(errno));
        close(mFd);
    }
    return result;
}

void Serial_UART::closeOnFAIL()
{

}