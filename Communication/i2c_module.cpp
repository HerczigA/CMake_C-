#include <stdint.h>
#include <sys/ioctl.h>
#include <string.h>
#include "communication.h"

using namespace std;

com_error_t I2C_Comm::initCommunication()
{
    int result = E_OK;
    result = initPacket();
    if(result == E_OK)
        result = get_I2C_Address();
    if(result == E_OK)
        result = Init_I2C();

    return result;
}

void I2C_Comm::setClock(uint32_t &clockSpeed) 
{ 
    if(mMaxSpeed >= clockSpeed)
        mClockSpeed = clockSpeed;
}


com_error_t I2C_Comm::get_I2C_Address()
{
    string pathOfI2CRequest ="i2c_address.txt";
    ifstream ifile;
    string line;
    com_error_t result = E_I2C_ADDRESS_NOK;
    system("sudo i2cdetect -y 1 > i2c_address.txt");
    //maybe delay does not need system blocking function call... 
    /*Blocking and non-blocking are just logical names to describe the behaviour
    of the functions. As the name implies, a blocking function blocks the calling
    function. This means the caller does not do anything until the blocking 
    function returns control to it. You can consider this synchronous behaviour, 
    because the interactions are "synchronized" in that the calling function must 
    wait until the called blocking function is finished before continuing.

    Conversely, non-blocking functions, of course, do the opposite: they do not 
    require the caller to wait until they are finished. They simply call the 
    function and immediately carry on to the next instruction to execute. 
    This could be thought of as "asynchronous" interaction.

    You could think of a personal, informal in-person conversation with someone
    as asynchronous. Each person doesn't necessarily wait until the other is 
    finished their sentence. In a professional, formal conversation with your 
    boss, its probably best to communicate synchronously: you do not want to 
    interrupt while your boss is talking. You wait for him/her to finish talking, 
    then you talk. (Aside: though your direction of communication with them is 
    probably synchronous, they may communicate with you asynchronously, 
    interrupting at will).

    N.B.: Note that there are technical and programming-specific keywords for 
    "synchronous", etc, so do not misuse these.
    delay(10);*/
    try
    {
        ifile.open(pathOfI2CRequest.c_str(), ifstream::in);
        if(!ifile.is_open())
           throw "could not open i2c file";
    }
    catch(const exception &msg)
    {
        syslog(LOG_ERR,"%s",msg.what());
        cout << msg.what() << endl;
        return E_I2C_FILE_OPEN_NOK;
    }
    int j =0;

    while(getline(ifile,line))
    {
        if(j == 0)
            j++;
        else
        {
            char *p,*k;
            p = new char[line.length()+1];
            k=p;

            strcpy(p,line.c_str());

            char *t;

            while(*p!= EOF || *p != '\n' )
            {
                if( *p == ':')
                {
                    p++;
                    while(!isdigit(*p))
                        p++;
                    t = p;
                    t++;
                    if(isdigit(*t))
                    {
                        mAddress = atoi(t);   //hex number also!
                        *t = 'a';
                        result = E_OK;
                    }
                    else
                    {
                        switch (*t)
                        {
                        case 'a':
                            mAddress = 10;
                            break;
                        case 'b':
                            mAddress = 11;
                            break;

                        case 'c':
                            mAddress = 12;
                            break;

                        case 'd':
                            mAddress = 13;
                            break;

                        case 'e':
                            mAddress = 14;
                            break;

                        case 'f':
                            mAddress = 15;
                            break;

                        default:
                            break;
                        }
                    }

                    mAddress += (16*atoi(p));
                    result = E_OK;
                    break;
                }
                p++;
            }
            delete[] k;
        }

    }
    cout << "I2C slave address : " << result << endl;
    syslog(LOG_INFO,"I2C slave address :%d ", (int)result);
    return result;
}

com_error_t I2C_Comm::Init_I2C()
{
    int result  = SerialComm_Error::E_OK;
    const string Path_I2C = "/dev/i2c-1";
    mFd = open(Path_I2C.c_str(),O_RDWR);
    if(mFd >= 0)
    {
        if(mAddress) 
        {
            if(ioctl(mFd, I2C_SLAVE, mAddress) < 0)
            {
                cout << "Unable to select I2C device " << strerror(errno) << endl;
                syslog(LOG_ERR,"Unable to select I2C device because: %s",strerror(errno));
                result = E_I2C_SELECT_NOK;    
            }
        }
        else
        {
            cout << "Cannot get the address for i2c slave"  << endl;
            syslog(LOG_ERR,"%s",strerror(errno));
            result = E_I2C_ADDRESS_NOK;
        }
    }
    else
    {
        cout<< "Could not open I2C.Try with sudo or check the path, wiring!" << endl;
        result = E_I2C_OPEN_NOK;
        syslog(LOG_ERR,"%s",strerror(errno));
    }
    
    return result;
}

com_error_t I2C_Comm::writeBytes(const char* packet, const int &length)
{
    com_error_t result = E_OK;
    if(!packet)
        return E_PACKET_NULLPTR;
    
    char data[mPacketLength];
    for(int i = 0; i < length; )
    {
        data[0]=packet[i++];
        if(i != length)
            data[1]=packet[i++];
        result = updatePacketForWrite(data);
        if(result == E_OK)
        {
            if(write(mFd, mWritePacket, mPacketLength)!= mPacketLength)
            {
                result = E_WRITE_NOK;
                syslog(LOG_ERR, "Write error in i2c at the number of %d package\n", i);
            }
        }    
    }
    
    return result;
}

com_error_t I2C_Comm::readBytes(char buffer[], const int &length)
{
    com_error_t result = E_OK;
    for(int i = 0; i < length; )
    {
        bzero(mReadPacket, mPacketLength);
        if(read(mFd, mReadPacket, mPacketLength) != mPacketLength)
        {
            result = E_READ_NOK;
            break;
        }
        buffer[i++]=mReadPacket[0];
        buffer[i++]=mReadPacket[1];
    }
    
    return result;
}