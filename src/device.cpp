#include "../hdr/device.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <bits/stdc++.h>
#include <wiringPi.h>
#include <softServo.h>

using namespace std;


void filehandler::getPatternFileName()
{
    cout << patternFile << endl;
}

void filehandler::getInfoFromPattern()
{
    try
    {
        fileHand.open(patternFile.c_str(), ios::in);
        
    }
    catch(fstream::failure e)
    {
        std::cerr << e.what() << '\n';
        std::cout << e.what() << "Exception under opening" << '\n';
        return;
    }
    while(getline(fileHand,lineFromFile))
        pattern.push_back(lineFromFile);

    fileHand.close();

}

void filehandler::getLinesFromVector()
{
    for(auto x : pattern)
        cout << x << endl;
}

void filehandler::processPattern()
{
    if(pattern.size() > 1)
        {
            while(pattern.size() != 1)
                pattern.erase(pattern.end());
        }

    auto temp = pattern[0];
    auto it = temp.begin();
    while(it != temp.end())
    {
        temp.erase(remove(temp.begin(),temp.end(),'-'),temp.end());
        ++it;
    }
    pattern[0] = temp;

}


void filehandler::FinishProcess()
{
    try
    {
        fileHand.open(newFile.c_str(),ios::out);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << e.what() << '\n';
        return;
    }

    fileHand << pattern[0];

    fileHand.close();
}

string device::get_Name()
{
    return name;
}

devType_t device::get_Dev_Type()
{

    return dev_Type;
}

Id_t device::get_ID()
{
    return id;
}

comm_t device::get_Comm_Type()
{
    return commType;
}

int device::Init_SPI(SPI_Frame spi)
{
    SPI_Frame FramePackage;
    FramePackage.ChipSelect = spi.ChipSelect;
    FramePackage.MOSIPin = spi.MOSIPin;
    FramePackage.MISOPin = spi.MISOPin;
    FramePackage.ClockPin = spi.ClockPin;
    FramePackage.clk_Pol_Pha = spi.clk_Pol_Pha;
    FramePackage.ClockSpeed = spi.ClockSpeed;
    FramePackage.Packet[SPI_PACKET_LENGTH];
    
    if(FramePackage.ChipSelect)
        pinMode(FramePackage.ChipSelect,OUTPUT);
    else


    if(FramePackage.MOSIPin)
        pinMode(FramePackage.MOSIPin,OUTPUT);
    
    if(FramePackage.MISOPin)
        pinMode(FramePackage.MISOPin,INPUT);
    
    if(FramePackage.ClockPin)
        pinMode(FramePackage.ChipSelect,OUTPUT);

}
int device::Init_I2C()
{
}

int device::Init_UART()
{
    
}

int device::Init_CAN()
{
}

int device::Init_Bluetooth()
{
}

int device::Init_Wifi()
{
}

/*void device::Init_Communication()
{

    switch(commType)
    {
        case SPI:
            Init_SPI();
            break;

        case I2C:
            Init_I2C();
            break;

        case CAN:
            Init_CAN();
            break;

        case UART:
            Init_UART();
            break;

        case Bluetooh:
            Init_Bluetooth();
            break;

        case Wifi:
            Init_Wifi();
            break;

        default:
            break;
    }

}*/

uint8_t device::setPins(vector<uint8_t> pinNumbers, uint8_t directions[], uint8_t numberOfPorts)
{
    int result = 0;

    if(pinNumbers.empty() || numberOfPorts >= MAX_PORTS_NUMBER )
    {
         cout << "Nullpointer for pinNumbers or too much number for ports bastard!? " << endl;
         result = 1;
    }
    else
    {
        uint8_t i = 0;
        auto pinEnd = pinNumbers.end();

        for(auto it = pinNumbers.begin(); it != pinEnd; ++it)
            ++i;
        if(i != numberOfPorts)
            result= 3;

        i=0;
	cout<<"before while i < NumberOfPorts " << endl;
        while(i < numberOfPorts)
        {

            if(pinNumbers[i] && directions[i])
            {
	        pinMode(pinNumbers[i],directions[i]);
		i++;
	    }
            else
            {
                cout<< " nullptr got" << endl;
                result = 2;
                break;
            }
        }
    }
    cout << "result = "<< result << endl;
    return result;

}
void actuator::pwm_Setup(vector<uint8_t> pinNumbers,  uint8_t numberOfPorts)
{

    int servoOut[] = {-1,-1,-1,-1,-1,-1,-1,-1};

     if(pinNumbers.empty() || numberOfPorts >= MAX_SERVO_PORTS )
    {
         cout << "Nullpointer for pinNumbers or too much number for ports bastard!? " << endl;
        return;
    }
    else
    {
        int8_t i  = 0;
        auto pinEnd = pinNumbers.end();
        for(auto it = pinNumbers.begin(); it != pinEnd; ++it)
            ++i;

        if(i != numberOfPorts)
          {

            cout<< " not equal the given port numbers = "
            <<(int) i << " and the gpio numbers = "
            <<(int) numberOfPorts << endl;
            return ;
          }

        for(auto j = 0; i >= 0; ++j)
        {
            servoOut[j] = pinNumbers[j];
            i--;
        }
        softServoSetup(servoOut[0],servoOut[1],servoOut[2],servoOut[3],servoOut[4],servoOut[5],servoOut[6],servoOut[7]);
        Initialized = true;
    }

}

void actuator::pwm_Write(uint8_t pinNumber, uint16_t DC, unsigned int lengthOfDelay)
{
    if(!Initialized)
        return;
    if(DC >= MAX_DC)
        DC = MAX_DC -1;

    pwmWrite(pinNumber,DC);
    delay(lengthOfDelay);

}
void actuator::pwm_Servo_Write_In_Loop(uint8_t pinNumber, int16_t DC, unsigned int lengthOfDelay, bool loop)
{
    if(!Initialized)
        return;
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

void actuator::pwm_Servo_Full_Limit(uint8_t pinNumber, time_ms_t t_length)
{
    if(!Initialized)
        return;
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

