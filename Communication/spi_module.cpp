// #include "communication.h"
// #include <iostream>

// const static std::string chn0 = "/dev/spidev0.0";
// const static std::string chn1 = "/dev/spidev0.1";

// using namespace std;

// SPI_Comm::SPI_Comm()
//     : SerialComm(MAX_SPI_CLK, MAX_SPI_PACKET_LENGTH)
//     , mChannelNumbers(1)
// {
//     for(size_t i = 0; i < mChannelNumbers ; i++)
//     {
//         mEndianess[i] =  0;
//         mClk_Pol_Pha[i] = SPI_MODE_0;
//     }
// }
// SPI_Comm::SPI_Comm(uint32_t clockSpeed, int length, uint8_t spiChannelNumbers)
//     : SerialComm(clockSpeed, length)
//     , mChannelNumbers((spiChannelNumbers > MAX_SPI_CHANNELS) || spiChannelNumbers == 0 ? MAX_SPI_CHANNELS : spiChannelNumbers) 
// {
//     for(size_t i = 0; i < mChannelNumbers ; i++)
//     {
//         mEndianess[i] =  0;
//         mClk_Pol_Pha[i] = SPI_MODE_0;
//     }
// }


// SPI_Comm::SPI_Comm(uint8_t endianess, int clk_Pol_Pha, uint32_t clockSpeed, int length, uint8_t spiChannelNumbers)
//     : SerialComm(clockSpeed, length)
//     , mChannelNumbers((spiChannelNumbers > MAX_SPI_CHANNELS) || spiChannelNumbers == 0 ? MAX_SPI_CHANNELS : spiChannelNumbers)
// {
//     for(size_t i = 0; i < MAX_SPI_CHANNELS ; i++)
//     {
//         mEndianess[i] =  endianess;
//         mClk_Pol_Pha[i] = clk_Pol_Pha;
//     }
// }

// com_error_t SPI_Comm::Init_SPI()
// {
    
//     com_error_t result =E_OK;
//     size_t cnt = 0;
//     size_t channel = 0;
//     size_t i = 0;
//     size_t limit = 0;
//     int spiChDiff = 0;
//     int WR_POLPHA_CNT = 0;
//     int RD_POLPHA_CNT = 0;
//     int WR_ENDIANESS_CNT = 0;
//     int RD_ENDIANESS_CNT = 0;
//     int WR_SPEED_CNT = 0;
//     int RD_SPEED_CNT = 0;
    
//     mFd = E_FD_NOK;
//     mFd2 = E_FD_NOK;
    
//     for(; i < mChannelNumbers; i++)
//     {   
//         string temp = mSpiChns[i];
//         mSpiFD[i] = open(chn0.c_str(), O_RDWR);
//         if(mSpiFD[i] < 0)
//            {
//                 cnt++;
//                 if(cnt == 1 && i == 1)
//                         channel++;
//                 if(cnt == MAX_SPI_CHANNELS)
//                 {
//                     syslog(LOG_ERR, "No fd[0] : %d  fd[1] : %d", mSpiFD[0], mSpiFD[1]);
//                     result = E_SPI_FD_OPEN;
//                 }   
//            }        
//     }
//     if(cnt == 1)
//     {
//         if(channel)
//         {
//             i = 0;
//             limit = 1;
//         }
//         else
//         {
//             i = 1;
//             limit = MAX_SPI_CHANNELS;
//         }

//     }
//     else
//     {
//         i = 0;
//         limit = MAX_SPI_CHANNELS;
//     }
    
//     spiChDiff = limit - i;
//     for(; i < limit; i++ )
//     {
//         if (ioctl (mSpiFD[i], SPI_IOC_WR_MODE, &mClk_Pol_Pha[i])< 0)
//         {
//             WR_POLPHA_CNT++;
//             cout<< "SPI Write Mode POL & Pha failure" << (string) mSpiChns[i] << endl;
//             syslog(LOG_ERR,"SPI Write Mode POL & Pha failure -> %s", strerror(errno));
//             if(WR_POLPHA_CNT == spiChDiff)
//             {
//                 result = E_SPI_PHA_POL;
//                 break;  
//             }
            
//         }

//         if (ioctl (mSpiFD[i], SPI_IOC_RD_MODE, &mClk_Pol_Pha[i])< 0)
//         {
//             RD_POLPHA_CNT++;
//             cout<< "SPI Read Mode POL & Pha failure" << (string) mSpiChns[i] << endl;
//             syslog(LOG_ERR,"SPI Read Mode POL & Pha failure -> %s", strerror(errno));
//             if(RD_POLPHA_CNT == spiChDiff)
//             {
//                 result = E_SPI_PHA_POL;
//                 break;  
//             }
            
//         }        
         
//         if (ioctl (mSpiFD[i], SPI_IOC_WR_LSB_FIRST, &mEndianess[i]) < 0)
//         {
//             WR_ENDIANESS_CNT++;
//             cout<< "SPI Read Mode LSB/MSB failure" << mSpiChns[i] << endl;
//             if(WR_ENDIANESS_CNT == spiChDiff)
//             {
//                 result =   E_SPI_ENDIANESS_NOK;
//                 break;  
//             }
//         }

//         if (ioctl (mSpiFD[i], SPI_IOC_RD_LSB_FIRST, &mEndianess[i]) < 0)
//         {
//             RD_ENDIANESS_CNT++;
//             cout<< "SPI Write Mode LSB/MSB failure" << mSpiChns[i] << endl;
//             if(RD_ENDIANESS_CNT == spiChDiff)
//             {
//                 result =   E_SPI_ENDIANESS_NOK;
//                 break;  
//             }
//         }

//         if (ioctl (mSpiFD[i], SPI_IOC_WR_MAX_SPEED_HZ,&mClockSpeed[i]) < 0)
//         {
//             WR_SPEED_CNT++;
//             cout<< "SPI Write Mode speed failure" << mSpiChns[i] << endl;
//            if(WR_SPEED_CNT == spiChDiff)
//             {
//                 result =   E_SPI_SPEED;
//                 break;  
//             }
//         }

//         if (ioctl (mSpiFD[i], SPI_IOC_RD_MAX_SPEED_HZ,&mClockSpeed[i]) < 0)
//         {
//             RD_SPEED_CNT++;
//             cout<< "SPI Read Mode speed failure" << mSpiChns[i] << endl;
//             if(RD_SPEED_CNT == spiChDiff)
//             {
//                 result =   E_SPI_SPEED;
//                 break;  
//             }
//         }
//     }
    
//     return result;
// }
