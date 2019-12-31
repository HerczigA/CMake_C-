#ifndef _PWM_HPP_
#define _PWM_HPP_


#include <vector>
#include "../hdr/parameters.hpp"
#ifdef RPI_VERSION
    #include <wiringPi.h>
#endif
#include <unistd.h>
#include <stdint.h>
using namespace std;

class PWMclass 
{
        std::unique_ptr<pwm_t> pwm_Type;
        int pwmRange;
        int initValue;

    public:
        PWMclass()
        {
            pwm_Type = std::make_unique<pwm_t>();
            initValue = 0;
            pwmRange = PWM_RANGE_MAX;
        }
        void set_pwm_Type(pwm_t &type);
        pwm_t pwm_Setup(vector<uint8_t> pinNumber);
        pwm_t pwm_ServoSetup(vector<uint8_t> pinNumbers,  uint8_t numberOfPorts);
        pwm_t Init_PWM(int pwm, vector<uint8_t> pinNumbers, uint8_t numberOfPorts);
        void pwm_Write(uint8_t pinNumber, int DC, time_ms_t  lengthOfDelay);
        void pwm_Write_Breathing(uint8_t pinNumber, time_ms_t  lengthOfDelay);
        void pwm_Servo_Write_In_Loop(uint8_t pinNumber, int16_t DC, time_ms_t lengthOfDelay, bool loop);
        void pwm_Servo_Full_Limit(uint8_t pinNumber,time_ms_t t_length);
        void pwm_Servo_Full_Limit(uint8_t pinNumber, time_ms_t t_length, bool button);
};

#endif