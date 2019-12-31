#include "pwm.hpp"
#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include <stdint.h>
using namespace std;


void PWMclass::set_pwm_Type(pwm_t &type)
{
    if(pwm_Type)
        pwm_Type.reset(&type);
}

pwm_t PWMclass::Init_PWM(int pwm, vector<uint8_t> pinNumbers, uint8_t numberOfPorts)
{

    pwm_t result = E_INIT_NOK;
    switch (pwm)
    {
            case simplePWM:
                result = pwm_Setup(pinNumbers);
                break;

            case ServoPWM:
                result = pwm_ServoSetup(pinNumbers,numberOfPorts);
                break;
            default:
                result = E_UNKNOW;
                break;
    }

    return result;
}

pwm_t PWMclass::pwm_ServoSetup(vector<uint8_t> pinNumbers,  uint8_t numberOfPorts)
{

    int servoOut[] = {-1,-1,-1,-1,-1,-1,-1,-1};
    pwm_t result = E_INIT_NOK;
     if(pinNumbers.empty() || numberOfPorts >= MAX_SERVO_PORTS )
         cout << "Nullpointer for pinNumbers or too much number for ports bastard!? " << endl;

    else
    {
        int8_t i  = 0;
        const auto pinEnd = pinNumbers.end();
        for(auto it = pinNumbers.begin(); it != pinEnd; ++it)
            ++i;

        if(i != numberOfPorts)
        {

            cout<< " not equal the given port numbers = "
            <<(int) i << " and the gpio numbers = "
            <<(int) numberOfPorts << endl;
        }
        else
        {
            for(auto j = 0; i >= 0; ++j)
            {
                servoOut[j] = pinNumbers[j];
                i--;
            }
            result = E_INIT_OK;
        }

        softServoSetup(servoOut[0],servoOut[1],servoOut[2],servoOut[3],servoOut[4],servoOut[5],servoOut[6],servoOut[7]);
    }
    return result;
}

pwm_t PWMclass::pwm_Setup(vector<uint8_t> pinNumber)
{
    pwm_t result = E_INIT_NOK;
    int pin = pinNumber[0];
    if( softPwmCreate(pin, initValue,  pwmRange) > E_INIT_NOK)
        result = E_INIT_OK;
        
    return result;
}

void PWMclass::pwm_Write(uint8_t pinNumber, int DC, time_ms_t lengthOfDelay)
{

    pwmWrite(pinNumber,DC);
    delay(lengthOfDelay);

}

void PWMclass::pwm_Write_Breathing(uint8_t pinNumber,time_ms_t lengthOfDelay)
{
    if(lengthOfDelay > 200)
        lengthOfDelay = 200;

    bool increase = true;
    for(auto i =0 ; ; )
    {
        increase ? ++i : i--;

        pwmWrite(pinNumber,i);
        delay(lengthOfDelay);

        if(i == MAX_DC )
            increase = false;
        else if(i == 0)
            increase = true;

    }
}

void PWMclass::pwm_Servo_Write_In_Loop(uint8_t pinNumber, int16_t DC,time_ms_t lengthOfDelay, bool loop)
{
    cout << "Start servo in Loop" << endl;
    time_ms_t delaytime = lengthOfDelay;

    if(delaytime <= MIN_SERVO_DELAY_TIME)
        delaytime = DEF_SERVO_TIME;

    if(loop)
    {
        while(loop)
        {
            softServoWrite(pinNumber,DC);
            delay(delaytime);
            DC -= SERVO_STEP;
            if(DC < SERVO_LOW_LIMIT)
                DC = SERVO_HIGH_LIMIT;
        }
    }
    else
    {
        softServoWrite(pinNumber,DC);
        delay(delaytime);
    }


}

void PWMclass::pwm_Servo_Full_Limit(uint8_t pinNumber, time_ms_t t_length)
{
    cout << "Start servo FULL Limit" << endl;
    time_ms_t delaytime = t_length;

    if(delaytime <= MIN_SERVO_DELAY_TIME)
        delaytime = DEF_SERVO_TIME;

    softServoWrite(pinNumber,DEF_SERVO_POSITION);
        delay(delaytime);

    while(true)
    {
        softServoWrite(pinNumber,SERVO_HIGH_LIMIT);
        delay(delaytime);
        softServoWrite(pinNumber,SERVO_LOW_LIMIT);
        delay(delaytime);
    }

}

void PWMclass::pwm_Servo_Full_Limit(uint8_t pinNumber, time_ms_t t_length, bool button)
{
    time_ms_t delaytime = t_length;

    if(delaytime <= MIN_SERVO_DELAY_TIME)
        delaytime = DEF_SERVO_TIME;

    static bool stateTop  = true;

    if(button && stateTop)
    {
        cout<< "servo high" << endl;
        softServoWrite(pinNumber,SERVO_HIGH_LIMIT);
        delay(delaytime);
        stateTop = false;
    }
    else if(!button && !stateTop)
    {
        cout<< "servo low" << endl;
        softServoWrite(pinNumber,SERVO_LOW_LIMIT);
        delay(delaytime);
        stateTop = true;
    }

}
