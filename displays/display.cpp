#include "display.hpp"
#include <iostream>
void LCD_1602::InitLCD()
{
        
        digitalWrite(RS,LOW);
        digitalWrite(RW,LOW);
        digitalWrite(EN,LOW);

        writingLCD4(0x03);
        delayMicroseconds(4500); // wait min 4.1ms

        // second try
        writingLCD4(0x03);
        delayMicroseconds(4500); // wait min 4.1ms
        
        // third go!
        writingLCD4(0x03); 
        delayMicroseconds(150);

        // finally, set to 4-bit interface
        writingLCD4(0x02);
            
        displayFunction = WIRE_4 | LINE_1 |FONT_5X8;
        SetFunction(displayFunction);
        
        displayEntryMod = ENTRY_CURSOR_LOW | SHIFT_OFF;
        EntryModeSet(displayEntryMod);

        displayON_OFF = DISPLAY_ON | CURSOR_ON | BLINK_ON;
        display();

        displayShifting = MOVE_LEFT_CURSOR | MOVE_LEFT_CURSOR;
        Cursor_Display_Shift(displayShifting);
        
        isInited = true;
}

void LCD_1602::SetFunction(uint8_t value)
{
    command(value);
}

void LCD_1602::EntryModeSet(uint8_t value)
{
    command(value);
}

void LCD_1602::Cursor_Display_Shift(uint8_t value)
{
    command(value);
}

void LCD_1602::WriteData(uint8_t *msg)
{
    (void) *msg;
    uint8_t temp = 0x33;    //test *msg =  0x33
    if(!modebus8)
    {
        for(auto j = 0; j < 2; j++)
        {
            isBusy = true;
            Check_Busy_Flag();
            if(!isBusy)
            {
                writingLCD4(temp);
                pulseEnable();
            }    
        }
    }
    /*else
    {
        isBusy = true;
        Check_Busy_Flag();
        if(!isBusy)
        {
            writingLCD4(temp);
            pulseEnable();
        }
    }*/
}

void LCD_1602::Check_Busy_Flag()
{
    bool busy1 = false;
    bool busy2 = false;
    pinMode(dataPins[3],INPUT); //last or least
    digitalWrite(EN,LOW);
    digitalWrite(RS,LOW);
    digitalWrite(RW,HIGH);
    digitalWrite(EN,HIGH);
    delay(100);
    busy1 = digitalRead(dataPins[3]) ? true : false;
    digitalWrite(EN,LOW);
    digitalWrite(EN,HIGH);
    delay(100);
    busy2 = digitalRead(dataPins[3]) ? true : false;
    digitalWrite(EN,LOW);
    digitalWrite(RW,LOW);
    pinMode(dataPins[3],OUTPUT);
#if TEST_DISPLAY_LCD  
    std::cout <<"busy1 (7th bit)= "<<(int) busy1 << std::endl;
    std::cout <<"busy2 (3th bit)= "<<(int) busy2 << std::endl;
#endif
    isBusy = busy1 | busy2;
    if(isBusy)
        syslog(LOG_NOTICE, "LCD was busy");    
}

void LCD_1602::ClearLCD()
{
    command(CLEAR_DISPLAY);
    syslog(LOG_INFO,"Clear LCD");
}

void LCD_1602::ReturnHome()
{
    command(RET_HOME);
    syslog(LOG_INFO,"Return home");
}


void LCD_1602::DisplaySwtichOnOFF(uint8_t state)
{
    
    if(displayState == state)
        return;
    else
    {
        displayON_OFF = DISPLAY_ON_CNTR;
        if(state  & 01)
            displayON_OFF |= DISPLAY_ON;    
        else
            displayON_OFF &= ~DISPLAY_ON;
    }

    Check_Busy_Flag();
    if(!isBusy)
    {
        command(displayON_OFF);        
        std::cout << "Display changed state SUCCES" <<(int) state << std::endl; 
    }        
    else
    {
        syslog(LOG_ERR,"DISPLAYON/OFF failed due to busy state");
        std::cout << "Display changed state FAILED" <<(int) state << std::endl; 
    }
    displayState = state;
}

void LCD_1602::SetDDRAM()
{

}

LCD_1602::~LCD_1602()
{
    delete[] dataPins;
}

void LCD_1602::noDisplay() 
{
  displayON_OFF &= ~DISPLAY_ON;
  Check_Busy_Flag();
  if(!isBusy)
    command(DISPLAY_ON_CNTR | displayON_OFF);
  std::cout << "display OFF" << std::endl;
 }

void LCD_1602::display() {
  displayON_OFF |= DISPLAY_ON;
  Check_Busy_Flag();
  if(!isBusy)
    command(DISPLAY_ON_CNTR | displayON_OFF);
  std::cout << "display ON" << std::endl;
}

inline void LCD_1602::command(uint8_t value) 
{
  send(value, LOW);
}

inline void LCD_1602::dataWriting(uint8_t value) 
{
  send(value, HIGH);
}

void LCD_1602::send(uint8_t value, uint8_t mode) {
    digitalWrite(RS, mode);
    digitalWrite(RW,LOW);
    writingLCD4(value);
    writingLCD4(value>>4);
}

void LCD_1602::writingLCD4(uint8_t data)
{
    for(auto i = 0; i < DLHALF; i++)
        digitalWrite(dataPins[i], (data >>i) & 0x01);
        pulseEnable(); 
}

void LCD_1602::pulseEnable()
{
    digitalWrite(EN,LOW);
    delayMicroseconds(1);  
    digitalWrite(EN,HIGH);
    delayMicroseconds(1);  
    digitalWrite(EN,LOW);
    delayMicroseconds(100);  
}



