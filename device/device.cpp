#include "device.h"
#include <softServo.h>
#include <softPwm.h>

static Id_t id_counter = 1;

device::device()
    : mDevice_Initialized{false}
{
    mId = 0;
    mDirections = nullptr;
    mDev_Type =  Unknown_device;
    mCommType =  Unknown_communication;
    wiringPiSetup();
}

device::device(string Name, Id_t ID, devType_t devtype,comm_t commtype)
    : mName{Name}
    , mDevice_Initialized(false)
{
    mId =( !ID && id_counter != 1 ) ? id_counter : id_counter++;
    mDirections = nullptr;
    mDev_Type = (devtype >= SENSOR && devtype <= SENSOR_ACTUATOR) ? devtype : Unknown_device;
    mCommType = (commtype >= SPI && commtype <= Bluetooth) ? commtype : Unknown_communication;
    wiringPiSetup();
}

device::~device()
{
    delete[] mDirections;
}

string &device::get_Name()
{
    return mName;
}

devType_t device::get_Dev_Type() const
{
    return mDev_Type;
}

Id_t device::get_ID() const
{
    return mId;
}

comm_t device::get_Comm_Type() const
{
    return mCommType;
}

uint8_t device::get_PinNumbers() const 
{
    return mPins.size();
}

uint8_t device::get_Pin(int i) const
{
    return mPins[i];
}

vector<uint8_t> &device::get_Pins()
{
    return mPins;
}

uint8_t device::get_Dirs(int i) const
{
    return mDirections[i];
}

void device::setName(string &devName)
{
    mName = devName;
}

void device::setdevType(devType_t dev )
{
    mDev_Type = dev;
}

void device::setPinNumbers(uint8_t pins)
{
    mPins.push_back(pins);
}

void device::setPinsForuC(uint8_t pins, uint8_t dirs)
{
    mPins.push_back(pins);
    mDirs.push_back(dirs);
}

void device::setID(Id_t id)
{
    if(!id || id < (id_counter-1) || id > id_counter)
        {

            mId = id_counter;
            id_counter++;

            #if DEBUG_DEVICE
                cout << "in if setid  " << id << " id_counter: " << id_counter<< " id: "<<id<< endl;
            #endif
        }

    else
        {
            mId = id;
            #if DEBUG_DEVICE
                cout << "in else setid  " << id << endl;
            #endif
        }

}

void device::setcommType(comm_t commType)
{
    mCommType = commType;
    int result = 0;
    switch(mCommType)
    {
        case SPI:
            result = mComm.Init_SPI(mComm.mSerialCom.spi);
            if(result)
                syslog(LOG_ERR, " SPI setup : %d ", result);
            break;

        case I2C:
            result = mComm.Init_I2C(mComm.mSerialCom.i2c);
            if(result)
                syslog(LOG_ERR, " I2C setup : %d ", result);
            break;

       /* case PWM:
            Init_PWM();
            break;*/

        case UART:
            result = mComm.Init_UART();
            if(result)
                syslog(LOG_ERR, " UART setup : %d ", result);
            break;

        case Bluetooth:
            //Init_Bluetooth();
            break;

        default:
            break;
    }
}

/*pwm_t actuator::Init_PWM(int pwm, vector<uint8_t> pinNumbers, uint8_t numberOfPorts)
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
}*/
/*
void device::Init_Communication()
{

    switch(commType)
    {
        case SPI:
            com.Init_SPI(com.mSerialCom.spi);
            break;

        case I2C:
            com.Init_I2C(com.mSerialCom.i2c);
            break;

        case PWM:
            Init_PWM();
            break;

        case UART:
            com.Init_UART();
            break;

        case Bluetooth:
            //Init_Bluetooth();
            break;

        default:
            break;
    }

}
*/
void sensor::digital_Read(int pin)
{
    if(pin >= MAX_PORTS_NUMBER)
        return;
        //should thrown exception

        if(digitalRead(pin))
        {
            delay(BUTTON_READ_TIME);
            buttonPushed = digitalRead(pin) ? true : false;
        }


        if(buttonPushed)
        {
#if DEBUG_DEVICE
            cout<< "button pushed" << endl;
#endif
            prevButtonState = buttonState;
            buttonState = !buttonState;

        }
        buttonPushed = false;

}

bool sensor::getButtonState()
{
    return buttonState;
}

bool sensor::buttonStateChanged()
{
    bool result = false;
    if(prevButtonState  != buttonState)
    {
        result = true;
        prevButtonState = buttonState;
        cout << "prevButtonState  != buttonState" << endl;
    }
    else
    {
        result = false;
    }

    return result;
}

uint8_t device::setPins(vector<uint8_t> pinNumbers)
{
    int result = 0;
    if(pinNumbers.empty() || pinNumbers.size() >= MAX_PORTS_NUMBER )
    {
         cout << "Empty vector has been received for pinNumbers\n or too much number for ports, bastard!? " << endl;
         result = 1;
    }
    else
    {
        uint8_t i = 0;
        const size_t pinSize = pinNumbers.size();
        while(i < pinSize)
        {

            int j = 0 ;
            switch (mDev_Type)
            {
                case SENSOR:
                    mDirections = new uint8_t[ mPins.size()];
                    if(!mDirections)
                    {
                        cout<< "no memory for alloc directions " << endl;
                        result = 4;
                        break;
                    }
                    while(j <  mPins.size())
                    {
                        mDirections[j] = INPUT;
                        j++;
                    }
                    break;

                case ACTUATOR:
                    mDirections = new uint8_t[mPins.size()];
                    if(!mDirections)
                    {
                        cout<< "no memory for alloc directions " << endl;
                        result = 4;
                        break;
                    }
                    j = 0;

                    while(j < mPins.size())
                    {
                        mDirections[j] = OUTPUT;
                        j++;

                    }
                    break;
                case SENSOR_ACTUATOR:
                    mDirections = new uint8_t[mPins.size()];
                    if(!mDirections)
                    {
                        cout<< "no memory for alloc directions " << endl;
                        result = 4;
                        break;
                    }
                    j = 0;
                    while(j < mPins.size())
                    {

                        mDirections[j] = mDirs[j] ? OUTPUT : INPUT;
                        j++;

                    }
                    break;

                default :
                    cout<< "default branch in setpins " << endl;
                    break;
            }
            //TODO: check the same size of pinnumbers and directions
	            pinMode(pinNumbers[i], mDirections[i]);
		        i++;

        }
    }
#if DEBUG_DEVICE
    cout << "result = "<< result << endl;
#endif
    return result;

}/*
pwm_t actuator::pwm_ServoSetup(vector<uint8_t> pinNumbers,  uint8_t numberOfPorts)
{

    int servoOut[] = {-1,-1,-1,-1,-1,-1,-1,-1};
    pwm_t result = E_INIT_NOK;
     if(pinNumbers.empty() || numberOfPorts >= MAX_SERVO_PORTS )
         cout << "Nullpointer for pinNumbers or too much number for ports bastard!? " << endl;

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
        device_Initialized = true;

    }
    return result;
}
pwm_t actuator::pwm_Setup(vector<uint8_t> pinNumber)
{
    pwm_t result = E_INIT_NOK;
    int pin = pinNumber[0];
    if( !softPwmCreate(pin, initValue,  pwmRange))
        {
            device_Initialized = true;
            result = E_INIT_OK;
        }
    return result;
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

void actuator::pwm_Servo_Full_Limit(uint8_t pinNumber, time_ms_t t_length, bool button)
{
    if(!device_Initialized)
        return;
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
*/