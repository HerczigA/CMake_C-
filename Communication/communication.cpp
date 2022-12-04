#include "communication.h"


void SerialComm::setPacketLength(int &length)
{ 
    mPacketLength = length;
}

com_error_t SerialComm::updatePacketForWrite(const char* packet)
{
    com_error_t result = E_OK;
    if(!packet)
    {
        result = E_UPDATE_PACKET_NOK;
        syslog(LOG_ERR, "Nullptr received in updatePacket()");
        
    }
    else
    {
        bzero(mWritePacket, mPacketLength);
        memcpy(mWritePacket, packet, mPacketLength);
    }
    
    return result;
}

com_error_t SerialComm::initPacket()
{
    com_error_t result = E_OK;
    mReadPacket = new char[mPacketLength];
    if(!mReadPacket)
    {
        syslog(LOG_ERR, " No memory for allocating serial com");
        result = E_INIT_PACKET_NOK;
    }
    mWritePacket = new char[mPacketLength];
    if(!mWritePacket)
    {
        syslog(LOG_ERR, " No memory for allocating serial com");
        result = E_INIT_PACKET_NOK;
    }
    return result;
}

SerialComm::~SerialComm()
{
    if(mReadPacket)
        delete mReadPacket;
    if(mWritePacket)
        delete mWritePacket;
}


Communication::Communication( )
    : mCommNok(false)
{
    mCommNok = wiringPiSetup();
    if(mCommNok)
    {
        mCommNok = wiringPiSetupGpio();
        if(!mCommNok)
        {
            mI2c = make_unique<I2C_Comm>();
            mUart = make_unique<Serial_UART>();    
        }
    }
}

bool Communication::getCommInitStatus() const
{
    return mCommNok;
}

int Communication::sendPackeges(SerialComm *writer , const char* package, const int & length)
{
    int result = writer->writeBytes(package, length);
    return result;
}

int Communication::getPackeges(SerialComm *receiver , char buffer[], const int & length)
{
    int result = receiver->readBytes(buffer, length);
    return result;
}