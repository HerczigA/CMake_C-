#ifndef _MAIN_INIT_HPP_
#define _MAIN_INIT_HPP_
#include <syslog.h>
#include <vector>
#include <memory>
#include "../hdr/device.hpp"

extern vector<unique_ptr<sensor>> Vec_Sensors;
extern vector<unique_ptr<actuator>> Vec_Actuators;
extern vector<unique_ptr<actuator>> Vec_SensActuators;

const uint8_t LCD_RW  = 5;
const uint8_t LCD_RS  = 6;
const uint8_t LCD_EN  = 10;
const uint8_t LCD_D7  = 15;
const uint8_t LCD_D6  = 16;
const uint8_t LCD_D5  = 1;
const uint8_t LCD_D4  = 4;
void InitBase();

#endif