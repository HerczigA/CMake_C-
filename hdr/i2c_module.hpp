#ifndef _I2C_MODULE_H
#define _I2C_MODULE_H

#include <stdint.h>

#define I2C_PACKET_LENGTH 16




struct I2C_Frame
{
    uint32_t ClockSpeed;
    uint8_t SDO;
    uint8_t SCL;
    char Packet[I2C_PACKET_LENGTH];
    uint16_t address;
};

#endif