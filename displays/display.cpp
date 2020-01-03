#include "display.hpp"
#include <syslog.h>
LCD_1602::InitLCD()
{

}

LCD_1602::LCD_1602(uint8_t EN, uint8_t RS, uint8_t RW, uint8_t *dataPins, const uint8_t numbOfPin)
{
    this->EN = EN;
    this->RS = RS;
    this->RW = RW;
    modebus8 = false;
    isBusy = true;
    
    for(auto i = 0; i < numbOfPin; i++)
        this->dataPins[i] = datapins[i];
    
    Init();
    
    
}

void LCD_1602::EntryModeSet()
{

}

void LCD_1602::Cursor_Display_Shift()
{

}

void LCD_1602::drivingLCD(uint8_t length, uint8_t *data)
{
    for(auto i = 0; i < length; i++)
    {
        pinsState[i] = *data & 0x01 ? HIGH : LOW; 
        *data >>= 1;
    }
    digital_Write(EN, HIGH);
                
    for(auto i = 0; i < length; i++)
        digitalWrite(dataPins[i], pinsState[i]);
    
    digital_Write(EN, LOW);
}



void LCD_1602::WriteData(uint8_t *msg)
{
    (void) *msg;
    uint8_t temp = 0x33;    //test *msg =  0x33
    #ifndef TEST_DISPLAY_LCD  
    for(auto *p = msg; *p; p++)
    {
    #endif

        if(!modebus8)
        {
            for(auto j = 0; j < 2; j++)
            {
                isBusy = true;
                while(isBusy)
                {
                    isBusy = Check_Busy_Flag();
                    if(!isBusy)
                        drivingLCD(DLHALF);
                }
                
            }
            
        }
        else
        {
            isBusy = true;
            while(isBusy)
            {
                isBusy = Check_Busy_Flag();
                if(!isBusy)
                    drivingLCD(DLHALF);
            }
            
        }
    #ifndef TEST_DISPLAY_LCD  
    }
    #endif
    
}

bool LCD_1602::Check_Busy_Flag()
{
    bool ret = false;
    digital_Write(RS,LOW);
    digital_Write(RW,HIGH);
    uint8_t busyFlag;
    /* D7 is busyflag -> 4 wire mode have to read twice !
    if(!modebus8)
    {
        for(auto i = 0; i < 2; i++)
        ret = digitalRead(dataPins[0]);
    }*/
    ret = digitalRead(dataPins[0]);
    
    return ret;
}

