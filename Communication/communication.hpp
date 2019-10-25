#pragma once 

#ifndef _COMMUNICATION_MODULE_H
#define _COMMUNICATION_MODULE_H

#include <stdint.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/spi/spidev.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <wiringPi.h>
#include <termios.h>
#include <unistd.h>

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


#define I2C_PACKET_LENGTH 16
#define SPI_PACKET_LENGTH 8
#define MAX_CLK 500000 //MAX speed 500kHz

#define MAX_SPI_CHANNELS 2

typedef uint8_t i2c_error_t;
typedef uint8_t spi_error;

enum I2C_error
{
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
    E_SPI_OK,
    E_SPI_SPEED,
    E_SPI_PHA_POL,
    E_SPI_FD_OPEN,
    E_SPI_ENDIANESS,
    E_SPI_UNKNOW,
    E_SPI_ALL
};

struct I2C_Frame
{
    uint32_t ClockSpeed;
    char Packet[I2C_PACKET_LENGTH];
    uint8_t address;
    int i2CFD;
};

struct term
{
    termios old;
    termios term;
    int BAUD;
    int uartFD;
};

struct SPI_Frame
{
    /*For Full duplex com-> ioctl(fd,SPI_IOC_MESSAGE,struct spi_ioc_transfer).
      Full duplex communication needs:
      Cross-compile with cross-gcc -I/path/to/cross-kernel/include
      if you don't work on the fixed hardware.
      For half duplex, read or write but just one at time read/write()... */
    uint32_t ClockSpeed[MAX_SPI_CHANNELS];
    std::vector<std::string> spiChns;
    int clk_Pol_Pha[MAX_SPI_CHANNELS];
    uint8_t endianess[MAX_SPI_CHANNELS];    //0 MSB other LSB
    char Packet[SPI_PACKET_LENGTH];
    int spiFD[MAX_SPI_CHANNELS];
    spi_ioc_transfer buffer;

};

struct serialcomm_t
{
    SPI_Frame spi;
    I2C_Frame i2c;
    term serialport;
};

class Communication_c
{
    public:
        spi_error Init_SPI(SPI_Frame spi);
        i2c_error_t Init_I2C(I2C_Frame i2c);
        //int Init_Bluetooth();
        serialcomm_t SerialCom; 
        int get_I2C_Address();
        int Init_UART();
    
};


#endif