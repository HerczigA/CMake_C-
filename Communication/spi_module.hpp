#ifndef _SPI_MODULE_H
#define _SPI_MODULE_H

#define SPI_PACKET_LENGTH 8
#define MAX_CLK 500000 //MAX speed 500kHz

#include <stdint.h>
#include <linux/spi/spidev.h>
#include <vector>

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
const static std::string chn0 = "/dev/spidev0.0";
const static std::string chn1 = "/dev/spidev0.1";

struct SPI_Frame
{
    uint32_t ClockSpeed[];
    std::vector <string> spiChns;
    int clk_Pol_Pha[];
    uint8_t endianess[];    //0 MSB other LSB
    char Packet[SPI_PACKET_LENGTH];
    int spiFD[2];

};


#endif