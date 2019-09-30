#ifndef _I2C_MODULE_H
#define _I2C_MODULE_H

#include <stdint.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <wiringPi.h>

#define I2C_PACKET_LENGTH 16



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

struct I2C_Frame
{
    uint32_t ClockSpeed;
    char Packet[I2C_PACKET_LENGTH];
    uint8_t address;
    int i2CFD;
};

typedef uint8_t i2c_error_t;

int getAddress();

#endif