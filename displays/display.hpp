#ifndef _DISPLAY_HPP_
#define _DISPLAY_HPP_

#include "../Adafruit-ST7735-TFT/Adafruit-SPITFT.h"
#include "../hdr/parameters.hpp"

//just an example how to give specific address to pointer in embedded
//volatile uint8_t * const LINE_0_SEGMENT_1 = (uint8_t *) 0x00;


#define DIGITS_IN_LINE 16
#define LINE_0_SEGMENT_1 0x00
#define LINE_0_SEGMENT_2 0x01
#define LINE_0_SEGMENT_3 0x02
#define LINE_0_SEGMENT_4 0x03
#define LINE_0_SEGMENT_5 0x04
#define LINE_0_SEGMENT_6 0x05
#define LINE_0_SEGMENT_7 0x06
#define LINE_0_SEGMENT_8 0x07
#define LINE_0_SEGMENT_9 0x08
#define LINE_0_SEGMENT_10 0x09
#define LINE_0_SEGMENT_11 0x0A
#define LINE_0_SEGMENT_12 0x0B
#define LINE_0_SEGMENT_13 0x0C
#define LINE_0_SEGMENT_14 0x0D
#define LINE_0_SEGMENT_15 0x0E
#define LINE_0_SEGMENT_16 0x0F

#define LINE_1_SEGMENT_1 0x40
#define LINE_1_SEGMENT_2 0x41
#define LINE_1_SEGMENT_3 0x42
#define LINE_1_SEGMENT_4 0x43
#define LINE_1_SEGMENT_5 0x44
#define LINE_1_SEGMENT_6 0x45
#define LINE_1_SEGMENT_7 0x46
#define LINE_1_SEGMENT_8 0x47
#define LINE_1_SEGMENT_9 0x48
#define LINE_1_SEGMENT_10 0x49
#define LINE_1_SEGMENT_11 0x4A
#define LINE_1_SEGMENT_12 0x4B
#define LINE_1_SEGMENT_13 0x4C
#define LINE_1_SEGMENT_14 0x4D
#define LINE_1_SEGMENT_15 0x4E
#define LINE_1_SEGMENT_16 0x4F

//RS = 0 W/R = 0
//HIGH FOR RS IS DATAREGISTER
//LOW FOR RS IS INSTRUCTIONREGISTER
//RS for high level R/W for low electricity data can be written at ordinary times
//For low electricity can be written instructions at ordinary times, or displays address,
// when RS for low level R/W high power for at ordinary times can read busy signal
//INTERFACE DL = 8 or 4 pins using -- 1 or 0
//INTERFACE N = two  line or one using -- 1 or 0 
//INTERFACE F = 5x10 dots or 5x7 dots using -- 1 or 0
#define DLFULL 8
#define DLHALF 4
#define CLEAR_DSP 0x01
#define RET_HOME 0x02
#define ENTRY_SET
#define DISPLAY_ON_CNTR 0x0F
#define INTERFACE_DL_8_N_2_F_1 0x3F
#define INTERFACE_DL_8_N_1_F_1 0x37
//it is for just 4 pins! ->When 4-bus mode, it needs to transfer 4-bit data twice.
#define INTERFACE_DL_4_N_2_F_1 0x2F 
#define INTERFACE_DL_4_N_1_F_1 0x27

//#define SET_CGRAM_DATA 0x0F
//#define SET_DDRAM_DATA 0xFx

// if RS = 1 W/R = 0 write data to address


/*
Pattern for special character
char heart[] = 
{
  B01010,
  B10101,
  B10001,
  B10001,
  B01010,
  B00100,
  B00000  
}
*/
class LCD_1602
{
  protected:
    volatile static  bool isBusy;
    uint8_t EN;
    uint8_t RS;
    uint8_t RW;
    int dataPins[];
    int pinsState[];
    char *message;
    bool modebus8;
    void InitLCD();
    void EntryModeSet();
    void Cursor_Display_Shift();
    bool Check_Busy_Flag();           //Done
    void drivingLCD(uint8_t length, uint8_t *data);  //Done

  public:
    LCD_1602(uint8_t EN, uint8_t RS, uint8_t RW, uint8_t *dataPins, const uint8_t numbOfPin);
    void WriteData(uint8_t *msg);     //Done
    void ClearLCD();
    void RerturHome();
    void DisplayON_OFF();
    void SetDDRAM();

    //TODO: cursor direction setup
    // Enable for writing phyically data out

};
/*
class display : public Adafruit_SPITFT, public LCD_1602
{

    std::unique_ptr<display_Type_t> displayType;
    




};*/


#endif
