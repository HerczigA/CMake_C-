#ifndef _PWM_OWN_HPP_
#define _PWM_OWN_HPP_


#include <vector>
#include "../hdr/parameters.hpp"
#include <unistd.h>
#include <stdint.h>
#include <softServo.h>
#include <softPwm.h>
#define MAX_PORTS_NUMBER 21
#define MAX_DC 1024
#define PWM_RANGE_MAX 100

#define MAX_SERVO_PORTS 8
#define SERVO_STEP 200
#define SERVO_HIGH_LIMIT 1050
#define SERVO_LOW_LIMIT -150
#define MIN_SERVO_DELAY_TIME 100
#define DEF_SERVO_TIME 200
#define DEF_SERVO_POSITION 500

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