#ifndef _SPI_MODULE_H
#define _SPI_MODULE_H

#define SPI_PACKET_LENGTH 8

#include <stdint.h>


struct SPI_Frame
{
    uint32_t ClockSpeed;
    int ClockPin;
    int ChipSelect;
    int MOSIPin;
    int MISOPin;
    int clk_Pol_Pha;
    char Packet[];

};


#endif