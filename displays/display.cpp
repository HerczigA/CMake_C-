#include "display.hpp"

LCD_1602::LCD_1602(uint8_t EN, uint8_t RS, uint8_t RW, uint8_t dataPins)
{
    this->EN = EN;
    this->RS = RS;
    this->RW = RW;
    this->dataPins = datapins;
}