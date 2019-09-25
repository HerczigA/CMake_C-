#ifndef _SPI_MODULE_H
#define _SPI_MODULE_H

#define SPI_PACKET_LENGTH 8
#define MAX_CLK 500000 //MAX speed 500kHz

#include <stdint.h>


struct SPI_Frame
{
    uint32_t ClockSpeed;
    int ClockPin;
    int ChipSelect;
    int MOSIPin;
    int MISOPin;
    int clk_Pol_Pha;
    uint8_t endianess;
    char Packet[];
    int spiFD;
};


#endif