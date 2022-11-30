#pragma once 

#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/spi/spidev.h>
#include <termios.h>
#include <unistd.h>
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

#ifndef I2C_PACKET_LENGTH
    #define I2C_PACKET_LENGTH 16
#endif

#ifndef SPI_PACKET_LENGTH
    #define SPI_PACKET_LENGTH 8
#endif

#ifndef MAX_SPI_CLK
    #define MAX_SPI_CLK 1000000 //MAX speed 1MHz
#endif

#ifndef MAX_SPI_CHANNELS
    #define MAX_SPI_CHANNELS 2
#endif

using i2c_error_t = uint8_t;
using spi_error = uint8_t;


enum I2C_error
{
    E_I2C_BAD_FD = -1,
    E_I2C_OK,
    E_I2C_OPEN,
    E_I2C_SELECT,
    E_I2C_SPEED_SET,
    E_I2C_FILE_OPEN,
    E_I2C_ADDRESS,
    E_I2C_UNKOW,
    E_I2C_ALL
};

enum errorSPI
{
    E_SPI_FD_BAD = -1,
    E_SPI_OK = 0,
    E_SPI_SPEED,
    E_SPI_PHA_POL,
    E_SPI_FD_OPEN,
    E_SPI_ENDIANESS,
    E_SPI_UNKNOW,
    E_SPI_ALL
};

struct I2C_Frame
{
    uint32_t mClockSpeed;
    char mPacket[I2C_PACKET_LENGTH];
    uint8_t mAddress;
    int i2CFD;
    I2C_Frame(){};
    I2C_Frame( uint32_t clockSpeed)
        : mClockSpeed(clockSpeed)
    {

    }
};

struct term
{
    termios oldTermios;
    termios term;
    int BAUD;
    speed_t uartFD;
};

struct SPI_Frame
{
    /*For Full duplex com-> ioctl(fd,SPI_IOC_MESSAGE,struct spi_ioc_transfer).
      Full duplex communication needs:
      Cross-compile with cross-gcc -I/path/to/cross-kernel/include
      if you don't work on the fixed hardware.
      For half duplex, read or write but just one at time read/write()... 

      Is the phase zero (CPHA = 0), then data is sampled at rising edge with CPOL=0
      and falling edge with CPOL=1. This behaviour switches with CPHA=1, then data is sampled at falling edge with CPOL=0 and rising edge with CPOL=1.
      MODE     CPOL    CPHA
        0   	0 	    0
        1 	    0 	    1
        2 	    1 	    0
        3 	    1 	    1
      */
    SPI_Frame()
    {
        for(size_t i = 0; i < MAX_SPI_CHANNELS ; i++)
        {
            mEndianess[i] =  0;
            mClk_Pol_Pha[i] = SPI_MODE_0;
            mClockSpeed[i] = MAX_SPI_CLK;
        }
        
    }
    SPI_Frame(uint8_t endianess, int clk_Pol_Pha, uint32_t ClockSpeed)
    {
        for(size_t i = 0; i < MAX_SPI_CHANNELS ; i++)
        {
            mEndianess[i] =  endianess;
            mClk_Pol_Pha[i] = clk_Pol_Pha;
            mClockSpeed[i] = ClockSpeed;
        }
        
    }
    uint32_t mClockSpeed[MAX_SPI_CHANNELS];
    std::vector<std::string> mSpiChns;
    int mClk_Pol_Pha[MAX_SPI_CHANNELS];
    uint8_t mEndianess[MAX_SPI_CHANNELS];    //0 MSB other LSB
    char mPacket[SPI_PACKET_LENGTH];
    int mSpiFD[MAX_SPI_CHANNELS];
    spi_ioc_transfer buffer;

};

struct SerialComm
{
    public:
        SerialComm(){};
    
    // private:
    SPI_Frame spi;
    I2C_Frame i2c;
    term serialport;
};

class Communication
{
    public:
        Communication(){};

    // private:
        spi_error Init_SPI(SPI_Frame spi);
        i2c_error_t Init_I2C(I2C_Frame i2c);
        //int Init_Bluetooth();
        SerialComm mSerialCom; 
        int get_I2C_Address();
        int Init_UART();
    
};
