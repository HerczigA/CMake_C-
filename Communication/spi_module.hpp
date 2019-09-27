#ifndef _SPI_MODULE_H
#define _SPI_MODULE_H

#define SPI_PACKET_LENGTH 8
#define MAX_CLK 500000 //MAX speed 500kHz

#include <stdint.h>
#include <linux/spi/spidev.h>
#include <string>
#include <string>
#include <vector>
#include <iostream>

#define MAX_SPI_CHANNELS 2

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
typedef uint8_t spi_error;

struct SPI_Frame
{
    uint32_t ClockSpeed[MAX_SPI_CHANNELS];
    std::vector<std::string> spiChns;
    int clk_Pol_Pha[MAX_SPI_CHANNELS];
    uint8_t endianess[MAX_SPI_CHANNELS];    //0 MSB other LSB
    char Packet[SPI_PACKET_LENGTH];
    int spiFD[MAX_SPI_CHANNELS];

};


#endif