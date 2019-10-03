#include "../hdr/device.hpp"
#include <iostream>
#include <string>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <bits/stdc++.h>
#include <wiringPi.h>
#include <softServo.h>
#include <softPwm.h>

using namespace std;

const static std::string chn0 = "/dev/spidev0.0";
const static std::string chn1 = "/dev/spidev0.1";


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

spi_error device::Init_SPI(SPI_Frame spi)
{
    (void) spi;
    spi_error result =E_SPI_OK;
    size_t cnt = 0;
    size_t channel = 0;
    size_t i = 0;
    size_t limit = 0;
    this->COM.spi.spiChns.push_back(chn0);
    
    this->COM.spi.spiChns.push_back(chn1);
    
    for(; i < MAX_SPI_CHANNELS; i++)
    {   string temp = COM.spi.spiChns[i];
        if(COM.spi.spiFD[i] = open(temp.c_str(), O_RDWR) < 0)
           {
               cnt++;
               if(cnt == 1 && i == 1)
                    channel++;
               if(cnt == MAX_SPI_CHANNELS)
                    result = E_SPI_FD_OPEN;
           }        
    }
    if(cnt)
    {
        if(channel)
        {
            i = 0;
            limit = 1;
        }
        else
        {
            i = 1;
            limit = MAX_SPI_CHANNELS;
        }

    }
    else
    {
        i = 0;
        limit = MAX_SPI_CHANNELS;
    }
     

    for(; i < limit; i++ )
    {
        if (ioctl (COM.spi.spiFD[i], SPI_IOC_WR_MODE, &COM.spi.clk_Pol_Pha[i])< 0)
        {
            cout<< "SPI Write Mode POL & Pha failure" << (string) COM.spi.spiChns[i] << endl;
            result = E_SPI_PHA_POL;
            break;
        }

        if (ioctl (COM.spi.spiFD[i], SPI_IOC_RD_MODE, &COM.spi.clk_Pol_Pha[i])< 0)
        {
            cout<< "SPI Read Mode POL & Pha failure" << COM.spi.spiChns[i] << endl;
            result = E_SPI_PHA_POL;
            break;
        }
         
        if (ioctl (COM.spi.spiFD[i], SPI_IOC_RD_LSB_FIRST, &COM.spi.endianess[i]) < 0)
        {
            cout<< "SPI Read Mode LSB/MSB failure" << COM.spi.spiChns[i] << endl;
            result = E_SPI_ENDIANESS;
            break;
        }

        if (ioctl (COM.spi.spiFD[i], SPI_IOC_WR_LSB_FIRST, &COM.spi.endianess[i]) < 0)
        {
            cout<< "SPI Write Mode LSB/MSB failure" << COM.spi.spiChns[i] << endl;
            result = E_SPI_ENDIANESS;
            break;
        }

        if (ioctl (COM.spi.spiFD[i], SPI_IOC_WR_MAX_SPEED_HZ,&COM.spi.ClockSpeed[i]) < 0)
        {
            cout<< "SPI Write Mode speed failure" << COM.spi.spiChns[i] << endl;
            result = E_SPI_SPEED;
            break;
        }

        if (ioctl (COM.spi.spiFD[i], SPI_IOC_RD_MAX_SPEED_HZ,&COM.spi.ClockSpeed[i]) < 0)
        {
            cout<< "SPI Read Mode speed failure" << COM.spi.spiChns[i] << endl;
            result = E_SPI_SPEED;
        }
    }

    return result;
}

i2c_error_t device::Init_I2C(I2C_Frame i2c)
{
    /*system(char* ) find i2c dev address!*/
    
    (void) i2c;
    i2c_error_t result  = E_I2C_OK;
    const string Path_I2C = "/dev/i2c-1";
    this->COM.i2c.i2CFD = open (Path_I2C.c_str(),O_RDWR );
    if(COM.i2c.i2CFD >= 0)
    {
        int temp = getAddress();
        if(temp) 
        {
            COM.i2c.address = temp;   
            if(ioctl(COM.i2c.i2CFD, I2C_SLAVE, COM.i2c.address) < 0)
            {
                cout << "Unable to select I2C device " << strerror(errno) << endl;
                result = E_I2C_SELECT;    
            }
        }
        else
        {
            cout << "address is 0"  << endl;
            result = E_I2C_ADDRESS;
        }
    }
    else
    {
        cout<< "can not open I2C.Try with sudo or check the path, wiring!" << endl;
        result = E_I2C_OPEN;
    }
    
    return result;
}

int device::Init_UART()
{
    vector<string> serial;
    serial.push_back("/dev/ttyUSB0");
    serial.push_back("/dev/ttyAMA0");
    serial.push_back("/dev/ttyS0");
    serial.push_back("/dev/ttyS1");

    /*if(!( init->numbOfDev ))
        return -1;
    */
    auto endOfDev = serial.end();
    for(auto it = serial.begin(); it != endOfDev; ++it)
    {
        const string temp = *it;
        COM.serialport.uartFD = open(temp.c_str(),O_RDWR | O_NOCTTY | O_NDELAY );    /* code */
        if(COM.serialport.uartFD > 0)   
            break;
    }
    
    if(COM.serialport.uartFD < 0)
        {
            cout <<"Invalid Filedescriptor\n" \
                   "maybe don't connect any wire or privilage not proper?" \
                   "Try with sudo"<<endl;
    //        syslog(LOG_ERR,"%s",strerror(errno));
            return -1;
        }
    fcntl(COM.serialport.uartFD,F_SETFL,O_RDWR);
    
    tcgetattr(COM.serialport.uartFD,&COM.serialport.old);
    COM.serialport.term.c_cflag = CS8 | CLOCAL | CREAD ;
    COM.serialport.term.c_iflag = IGNPAR;
    COM.serialport.term.c_lflag &= ~( ICANON | ECHO | ISIG);
    COM.serialport.term.c_oflag =0;
    COM.serialport.term.c_cc[VTIME]=0;
    COM.serialport.term.c_cc[VMIN]=0;
    cfsetispeed(&COM.serialport.term,(speed_t)&COM.serialport.BAUD);
    cfsetospeed(&COM.serialport.term,(speed_t)&COM.serialport.BAUD);

    tcflush(COM.serialport.uartFD, TCIOFLUSH);
    if(!tcsetattr(COM.serialport.uartFD,TCSANOW,&COM.serialport.term))
        {
          
            cout <<"Serial port has succesfully initialized" << endl;
            //syslog(LOG_INFO,"Serial port OK");
            return 0;
        }
    else
        {
            //closeOnFAIL(init);
            
            //syslog(LOG_ERR,"%s %d",strerror(errno),COM.serialport.uartFD);
            close(COM.serialport.uartFD);
            return -1;
        }


}
/*
int device::Init_CAN()
{
    return 0;
}
*/
int device::Init_Bluetooth()
{
    return 0;
}

void device::Init_Communication()
{

    switch(commType)
    {
        case SPI:
            Init_SPI(COM.spi);
            break;

        case I2C:
            Init_I2C(COM.i2c);
            break;

       /* case CAN:
            Init_CAN();
            break;*/

        case UART:
            Init_UART();
            break;

        case Bluetooth:
            Init_Bluetooth();
            break;

        default:
            break;
    }

}

void sensor::digital_Read(int pin)
{
    if(pin >= MAX_PORTS_NUMBER)
        return;
    
    buttonPushed = digitalRead(pin) ?  true : false;
    
}

bool sensor::getButtonState()
{
    return buttonPushed;
}


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


        while(i < numberOfPorts)
        {
            if((this->dev_Type == Actuator && directions[i] == INPUT) || (this->dev_Type == Sensor && directions[i] == OUTPUT)) 
            {
                result=4;   //can not be actuator input and vice versa
                break;
            }
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
void actuator::pwm_ServoSetup(vector<uint8_t> pinNumbers,  uint8_t numberOfPorts)
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
        device_Initialized = true;
    }

}
void actuator::pwm_Setup(int pinNumber)
{
    if( !softPwmCreate(pinNumber,this->initValue, this->pwmRange))
        device_Initialized = true;
}

void actuator::pwm_Write(uint8_t pinNumber, int DC, time_ms_t lengthOfDelay)
{
    if(!device_Initialized)
        return;

    pwmWrite(pinNumber,DC);
    delay(lengthOfDelay);

}

void actuator::pwm_Write_Breathing(uint8_t pinNumber,time_ms_t lengthOfDelay)
{
    if(!device_Initialized)
        return;
    
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

void actuator::pwm_Servo_Write_In_Loop(uint8_t pinNumber, int16_t DC,time_ms_t lengthOfDelay, bool loop)
{
    if(!device_Initialized)
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
    if(!device_Initialized)
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

void actuator::digital_Write(vector<int> pinNumbers, vector<int> states )
{
    if(pinNumbers.empty() || states.empty())
    {
        cout << "some arguments are empty" << endl;
    }
    if(pinNumbers.size() == states.size())
    {
        auto endOfVector = pinNumbers.end();

        for(auto it = pinNumbers.begin(); it != endOfVector; it++)
            digitalWrite(pinNumbers[*it],states[*it]) ;
    }
}