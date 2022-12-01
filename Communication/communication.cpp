#include "communication.h"

void SerialComm::setClock(uint32_t &clockSpeed) 
{ 
    if(mMaxSpeed >= clockSpeed)
        mClockSpeed = clockSpeed;
}

void SerialComm::setPacketLength(int &length)
{ 
    mLength = length;
}

com_error_t SerialComm::updatePacketForWrite(char* packet, int &length)
{
    com_error_t result = E_OK;
    if(!packet || mLength < length)
    {
        result = E_UPDATE_PACKET_NOK;
        syslog(LOG_ERR, "Too big the length or nullptr received in serial com");
        
    }
    else
    {
        bzero(mWritePacket, mLength);
        memcpy(mWritePacket, packet, length);
    }
    
    return result;
}

com_error_t SerialComm::initPacket()
{
    com_error_t result = E_OK;
    mReadPacket = new char[mLength];
    if(!mReadPacket)
    {
        syslog(LOG_ERR, " No memory for allocating serial com");
        result = E_INIT_PACKET_NOK;
    }
    mWritePacket = new char[mLength];
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


com_error_t SerialComm::writeBytes(char* packet, int length)
{
    com_error_t result = updatePacketForWrite(packet, length);
    if(result == E_OK)
    {
        if(write(mFd, mWritePacket, mLength)!= mLength)
        {
            result = E_WRITE_NOK;
        }
    }
    return result;
}

com_error_t SerialComm::readBytes()
{
    com_error_t result = E_OK;
    bzero(mReadPacket, mLength);
    if(read(mFd, mReadPacket, mLength)!= mLength)
    {
        result = E_READ_NOK;
    }
    return result;
}