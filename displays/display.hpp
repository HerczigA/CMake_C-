#ifndef _DISPLAY_HPP_
#define _DISPLAY_HPP_

//#include "../Adafruit-ST7735-TFT/Adafruit_ST7735.h"
#include "../hdr/parameters.hpp"
#include <syslog.h>

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

//HIGH FOR RS IS DATAREGISTER
//LOW FOR RS IS INSTRUCTIONREGISTER

#define CLEAR_DISPLAY 0x01
#define RET_HOME 0x02
#define ENTRY_SET 0x04
#define DISPLAY_ON_CNTR 0x08
#define CURSOR_DISPLAY_SHIFT 0x10
#define FUNCTION_SET 0x20
#define SETCGRAM 0x40
#define SETDDRAM 0x80

//ENTRY_SETUP
#define ENTRY_CURSOR_RIGHT 0x02
#define ENTRY_CURSOR_LOW 0x00
#define SHIFT_ON 0x01
#define SHIFT_OFF 0x00

//DISPLAY-CURSOR-BLINK_SETUP
#define DISPLAY_ON 0x04
#define DISPLAY_OFF 0x00
#define CURSOR_ON 0x02
#define CURSOR_OFF 0x00
#define BLINK_ON 0x01
#define BLINK_OFF 0x00

//Cursor or displayshift
#define MOVE_LEFT_CURSOR 0x00
#define MOVE_RIGHT_CURSOR 0x04
#define MOVE_LEFT_DISPLAY 0x08
#define MOVE_RIGHT_DISPLAY 0x0C

//Function setup
#define WIRE_8 0x10
#define WIRE_4 0x00
#define LINE_2 0x08
#define LINE_1 0x00
#define FONT_5X11 0x04
#define FONT_5X8 0x00


/*
Pattern for special character soon CGRAM
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
const uint8_t DLFULL = 8;
const uint8_t DLHALF = 4;

class LCD_1602
{
  protected:
    
    bool isBusy = true;
    bool isInited = false;
    uint8_t EN;
    uint8_t RS;
    uint8_t RW;
    uint8_t displayFunction;
    uint8_t displayEntryMod;
    uint8_t displayON_OFF;
    uint8_t displayShifting;
    int *dataPins;
    const uint8_t DLENGTH ;
    bool modebus8 = false;
    bool displayState = false;
    void InitLCD();   //Done
    void EntryModeSet(uint8_t value);
    void Cursor_Display_Shift(uint8_t value);
    void SetFunction(uint8_t value);
    void pulseEnable();
    void writingLCD4(uint8_t data);  //Done
    void dataWriting(uint8_t value);
    void command(uint8_t value);
    void send(uint8_t value, uint8_t mode); 
  public:
    LCD_1602(uint8_t EN, uint8_t RS, uint8_t RW, uint8_t *dataPins, uint8_t numbOfPin):
      EN {EN},
      RS {RS},
      RW {RW},
      DLENGTH {numbOfPin == DLHALF ? DLHALF : DLFULL}
      {
          displayFunction = FUNCTION_SET;
          displayEntryMod = ENTRY_SET;
          displayON_OFF = DISPLAY_ON_CNTR;
          displayShifting = CURSOR_DISPLAY_SHIFT;
          this->dataPins = new int[DLENGTH];
          
          if(!(this->dataPins))
              syslog(LOG_ERR,"cannot new memory for datapins in LCD");

          for(auto i = 0; i < DLENGTH; i++)
              this->dataPins[i] = dataPins[i];
          
          delayMicroseconds(20);
          InitLCD();
      }
    void Check_Busy_Flag();           //Done
    void WriteData(uint8_t *msg);     //Done
    void ClearLCD();    //Done
    void ReturnHome();
    void DisplaySwtichOnOFF(uint8_t state);
    void display();
    void noDisplay();
   
    void SetDDRAM();
    ~LCD_1602();
    //TODO: cursor direction setup
    // Enable for writing phyically data out

};

/*
class display : public Adafruit_SPITFT, public LCD_1602
{

    std::unique_ptr<display_Type_t> displayType;
    




};*/
#endif
