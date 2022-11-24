#include "communication.h"
#include <iostream>

const static std::string chn0 = "/dev/spidev0.0";
const static std::string chn1 = "/dev/spidev0.1";

using namespace std;


spi_error Communication_c::Init_SPI(SPI_Frame spi)
{
    (void) spi;
    spi_error result =E_SPI_OK;
    size_t cnt = 0;
    size_t channel = 0;
    size_t i = 0;
    size_t limit = 0;
    int spiChDiff = 0;
    int WR_POLPHA_CNT = 0;
    int RD_POLPHA_CNT = 0;
    int WR_ENDIANESS_CNT = 0;
    int RD_ENDIANESS_CNT = 0;
    int WR_SPEED_CNT = 0;
    int RD_SPEED_CNT = 0;
    
    SerialCom.spi.spiFD[0] = E_BAD_FD;
    SerialCom.spi.spiFD[1] = E_BAD_FD;
    SerialCom.spi.spiChns.push_back(chn0);
    
    SerialCom.spi.spiChns.push_back(chn1);
    
    for(; i < MAX_SPI_CHANNELS; i++)
    {   
        string temp = SerialCom.spi.spiChns[i];
        SerialCom.spi.spiFD[i] = open(temp.c_str(), O_RDWR);
        if(SerialCom.spi.spiFD[i] < 0)
           {
                cnt++;
                if(cnt == 1 && i == 1)
                        channel++;
                if(cnt == MAX_SPI_CHANNELS)
                {
                    syslog(LOG_ERR, "No fd[0] : %d  fd[1] : %d", SerialCom.spi.spiFD[0], SerialCom.spi.spiFD[1]);
                    result = E_SPI_FD_OPEN;
                }   
           }        
    }
    if(cnt == 1)
    {
        if(channel)
        {
            i = 0;
            limit = 1;
        }
        else
        {
            i = 1;
            limit = MAX_SPI_CHANNELS;
        }

    }
    else
    {
        i = 0;
        limit = MAX_SPI_CHANNELS;
    }
    
    spiChDiff = limit - i;
    for(; i < limit; i++ )
    {
        if (ioctl (SerialCom.spi.spiFD[i], SPI_IOC_WR_MODE, &SerialCom.spi.clk_Pol_Pha[i])< 0)
        {
            WR_POLPHA_CNT++;
            cout<< "SPI Write Mode POL & Pha failure" << (string) SerialCom.spi.spiChns[i] << endl;
            syslog(LOG_ERR,"SPI Write Mode POL & Pha failure -> %s", strerror(errno));
            if(WR_POLPHA_CNT == spiChDiff)
            {
                result = E_SPI_PHA_POL;
                break;  
            }
            
        }

        if (ioctl (SerialCom.spi.spiFD[i], SPI_IOC_RD_MODE, &SerialCom.spi.clk_Pol_Pha[i])< 0)
        {
            RD_POLPHA_CNT++;
            cout<< "SPI Read Mode POL & Pha failure" << (string) SerialCom.spi.spiChns[i] << endl;
            syslog(LOG_ERR,"SPI Read Mode POL & Pha failure -> %s", strerror(errno));
            if(RD_POLPHA_CNT == spiChDiff)
            {
                result = E_SPI_PHA_POL;
                break;  
            }
            
        }        
         
        if (ioctl (SerialCom.spi.spiFD[i], SPI_IOC_WR_LSB_FIRST, &SerialCom.spi.endianess[i]) < 0)
        {
            WR_ENDIANESS_CNT++;
            cout<< "SPI Read Mode LSB/MSB failure" << SerialCom.spi.spiChns[i] << endl;
            if(WR_ENDIANESS_CNT == spiChDiff)
            {
                result =   E_SPI_ENDIANESS;
                break;  
            }
        }

        if (ioctl (SerialCom.spi.spiFD[i], SPI_IOC_RD_LSB_FIRST, &SerialCom.spi.endianess[i]) < 0)
        {
            RD_ENDIANESS_CNT++;
            cout<< "SPI Write Mode LSB/MSB failure" << SerialCom.spi.spiChns[i] << endl;
            if(RD_ENDIANESS_CNT == spiChDiff)
            {
                result =   E_SPI_ENDIANESS;
                break;  
            }
        }

        if (ioctl (SerialCom.spi.spiFD[i], SPI_IOC_WR_MAX_SPEED_HZ,&SerialCom.spi.ClockSpeed[i]) < 0)
        {
            WR_SPEED_CNT++;
            cout<< "SPI Write Mode speed failure" << SerialCom.spi.spiChns[i] << endl;
           if(WR_SPEED_CNT == spiChDiff)
            {
                result =   E_SPI_SPEED;
                break;  
            }
        }

        if (ioctl (SerialCom.spi.spiFD[i], SPI_IOC_RD_MAX_SPEED_HZ,&SerialCom.spi.ClockSpeed[i]) < 0)
        {
            RD_SPEED_CNT++;
            cout<< "SPI Read Mode speed failure" << SerialCom.spi.spiChns[i] << endl;
            if(RD_SPEED_CNT == spiChDiff)
            {
                result =   E_SPI_SPEED;
                break;  
            }
        }
    }
    
    return result;
}
