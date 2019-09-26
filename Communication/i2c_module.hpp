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

int getAddress();
/*
int getAddress()
{
    std::string resultI2CAddress ="i2c_address.txt";
    std::ifstream ifile;
    std::string line;
    int result =0;
    system("sudo i2cdetect -y 1 > i2c_address.txt");
    delay(10);
    try
    {
        ifile.open(resultI2CAddress.c_str(), std::ifstream::in);
        if(!ifile.is_open())
           throw "could not open i2c file"; 
    }
    catch(const std::string msg)
    {
        std::cerr << msg << std::endl;
        std::cout << msg << std::endl;
        return E_I2C_FILE_OPEN;
    }
    int j =0;
    
    while(getline(ifile,line))
    {   
        if(j == 0)
            j++;
        else
        {
            char *p,*k;
            p = new char[line.length()+1];
            k=p;
            
            strcpy(p,line.c_str());
             
            char *t;
             
            while(*p!= EOF || *p != '\n' )
            {
                if( *p == ':')
                {
                    p++;
                    while(!isdigit(*p))
                        p++;
                    t = p;
                    t++;
                    if(isdigit(*t))
                    {
                        result = atoi(t);   //hex number also! 
                        *t = 'a';
                    }
                    else
                    {
                        switch (*t)
                        {
                        case 'a':
                            result = 10;
                            break;
                        case 'b':
                            result = 11;
                            break;
                        
                        case 'c':
                            result = 12;
                            break;
                        
                        case 'd':
                            result = 13;
                            break;
                        
                        case 'e':
                            result = 14;
                            break;
                        
                        case 'f':
                            result = 15;
                            break;

                        default:
                            break;
                        }
                    }

                    result = result + (16*atoi(p));
                    break;
                }
                p++;
            }
            delete[] k;
        }
            
    }
    return result;
}*/
#endif