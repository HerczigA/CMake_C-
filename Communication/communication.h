#pragma once 


#include <linux/i2c-dev.h>
#include <linux/spi/spidev.h>
#include <termios.h>
#include "parameters.h"

/*
    BCM2835_SPI_CLOCK_DIVIDER_65536 = 0,       ///< 65536 = 262.144us = 3.814697260kHz (total H+L clock period) 
		BCM2835_SPI_CLOCK_DIVIDER_32768 = 32768,   ///< 32768 = 131.072us = 7.629394531kHz
		BCM2835_SPI_CLOCK_DIVIDER_16384 = 16384,   ///< 16384 = 65.536us = 15.25878906kHz
		BCM2835_SPI_CLOCK_DIVIDER_8192  = 8192,    ///< 8192 = 32.768us = 30/51757813kHz
		BCM2835_SPI_CLOCK_DIVIDER_4096  = 4096,    ///< 4096 = 16.384us = 61.03515625kHz
		BCM2835_SPI_CLOCK_DIVIDER_2048  = 2048,    ///< 2048 = 8.192us = 122.0703125kHz
		BCM2835_SPI_CLOCK_DIVIDER_1024  = 1024,    ///< 1024 = 4.096us = 244.140625kHz
		BCM2835_SPI_CLOCK_DIVIDER_512   = 512,     ///< 512 = 2.048us = 488.28125kHz
		BCM2835_SPI_CLOCK_DIVIDER_256   = 256,     ///< 256 = 1.024us = 976.5625MHz
		BCM2835_SPI_CLOCK_DIVIDER_128   = 128,     ///< 128 = 512ns = = 1.953125MHz
		BCM2835_SPI_CLOCK_DIVIDER_64    = 64,      ///< 64 = 256ns = 3.90625MHz
		BCM2835_SPI_CLOCK_DIVIDER_32    = 32,      ///< 32 = 128ns = 7.8125MHz
		BCM2835_SPI_CLOCK_DIVIDER_16    = 16,      ///< 16 = 64ns = 15.625MHz
		BCM2835_SPI_CLOCK_DIVIDER_8     = 8,       ///< 8 = 32ns = 31.25MHz
		BCM2835_SPI_CLOCK_DIVIDER_4     = 4,       ///< 4 = 16ns = 62.5MHz
		BCM2835_SPI_CLOCK_DIVIDER_2     = 2,       ///< 2 = 8ns = 125MHz, fastest you can get
		BCM2835_SPI_CLOCK_DIVIDER_1     = 1,       ///< 1 = 262.144us = 3.814697260kHz, same as 0/65536
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_128);
    
*/

using com_error_t = uint8_t;


class SerialComm
{
    public:
    
        enum SerialComm_Error
        {
            E_OK = 0,
            E_FD_NOK,
            E_FD_ALLOC_NOK,
            E_INIT_PACKET_NOK,
            E_READ_NOK,
            E_WRITE_NOK,
            E_UPDATE_PACKET_NOK,
            E_I2C_OPEN_NOK,
            E_I2C_SELECT_NOK,
            E_I2C_SPEED_SET_NOK,
            E_I2C_FILE_OPEN_NOK,
            E_I2C_ADDRESS_NOK,
            E_UART_SETUP_NOK,
            E_SPI_SPEED_NOK,
            E_SPI_PHA_POL_NOK,
            E_SPI_FD_OPEN_NOK,
            E_SPI_ENDIANESS_NOK,
            E_PACKET_NULLPTR
        };

        SerialComm(){};
        SerialComm(uint32_t clockSpeed, int packetLength)
        : mClockSpeed(clockSpeed)
        , mPacketLength(packetLength)
        {
            
        };
        virtual ~SerialComm();
        virtual com_error_t initCommunication() = 0;
        virtual com_error_t writeBytes(const char* packet,const  int &length) = 0;
        virtual com_error_t readBytes(char buffer[], const int &length) = 0;
        
        void setPacketLength(int &length);
        
    protected:
        com_error_t updatePacketForWrite(const char* packet);
        int mFd;
        com_error_t initPacket(); 
        uint32_t mClockSpeed;
        int mPacketLength;
        char* mReadPacket;
        char* mWritePacket;
        
};

class I2C_Comm : public SerialComm
{
    public:
        I2C_Comm()
        : SerialComm(I2C_MAX_SPEED, I2C_MAX_PACKET_LENGTH) 
        , mMaxSpeed(I2C_MAX_SPEED) 
        , mAddress(0)
        {

        };
        I2C_Comm(uint32_t clockSpeed, uint length)
        : SerialComm(clockSpeed, length)  
        , mMaxSpeed(I2C_MAX_SPEED)
        , mAddress(0)
        {

        };
        com_error_t initCommunication() override;
        com_error_t writeBytes(const char* packet,const int &length) override;
        com_error_t readBytes(char buffer[], const int &length) override;
        void setClock(uint32_t &clockSpeed);
    private:
        com_error_t get_I2C_Address();
        com_error_t Init_I2C();
        uint32_t mMaxSpeed;
        uint8_t mAddress;
        
};

class Serial_UART : public SerialComm
{
    public:
        Serial_UART(){};
        com_error_t initCommunication() override;
        com_error_t writeBytes(const char* packet,const int &length) override;
        com_error_t readBytes(char buffer[], const int &length) override;
        void setBaud(const int& baud);
    private:
        set<int> mBaudrates={4800, 9600,
                            19200, 38400,
                            57600, 115200,
                            230400,460800,
                            500000 };
        void closeOnFAIL();
        termios mOldTermios;
        termios mTerm;
        int mBAUD;
    
};

// class SPI_Comm : public SerialComm
// {
//     /*For Full duplex com-> ioctl(fd,SPI_IOC_MESSAGE,struct spi_ioc_transfer).
//       Full duplex communication needs:
//       Cross-compile with cross-gcc -I/path/to/cross-kernel/include
//       if you don't work on the fixed hardware.
//       For half duplex, read or write but just one at time read/write()... 

//       Is the phase zero (CPHA = 0), then data is sampled at rising edge with CPOL=0
//       and falling edge with CPOL=1. This behaviour switches with CPHA=1, then data is sampled at falling edge with CPOL=0 and rising edge with CPOL=1.
//       MODE     CPOL    CPHA
//         0   	0 	    0
//         1 	    0 	    1
//         2 	    1 	    0
//         3 	    1 	    1*/
      
//      public:
//         SPI_Comm();
//         SPI_Comm(uint32_t clockSpeed, int length, uint8_t spiChannelNumbers);
//         SPI_Comm(uint8_t endianess, int clk_Pol_Pha, uint32_t clockSpeed, int length, uint8_t spiChannelNumbers);
//         com_error_t Init_SPI();
//         int mClk_Pol_Pha[MAX_SPI_CHANNELS];
//         void setClock(uint32_t &clockSpeed);
//         uint8_t mEndianess[MAX_SPI_CHANNELS];    //0 MSB other LSB
//         private:
//             int mFd2;
//             uint8_t mChannelNumbers;
//             // spi_ioc_transfer buffer;
// };



class Communication
{
    public:
        Communication( );
        bool getCommInitStatus() const ;
        int sendPackeges(SerialComm *writer , const char* package, const int & length);
        int getPackeges(SerialComm *receiver , char buffer[], const int & length);

    private:
        unique_ptr<I2C_Comm> mI2c;
        unique_ptr<Serial_UART> mUart;
        bool mCommNok;
        
};
