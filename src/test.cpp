#include "../hdr/test.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <bits/stdc++.h>
#include <wiringPi.h>
#include <stdio.h>
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
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << e.what() << '\n';
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

string device::getName()
{
    return name;
}

devType_t device::getType()
{
 
    return dev_Type < DEVTYPE ? dev_Type : 0;
}

Id_t device::getID()
{
    return id;
}


uint8_t device::setPins(uint8_t pinNumbers[], uint8_t directions[], uint8_t numberOfPorts)
{
    int result = 0;

    if(!pinNumbers || numberOfPorts >= MAX_PORTS_NUMBER )
    {
         cout << "Nullpointer for pinNumbers or too much number for ports bastard!? " << endl;
         result = 1;
    }
    else
    {
        uint8_t i = 0;
        while(pinNumbers++)
            i++;
        if(i != numberOfPorts)
            result= 3;
        
        i=0;
        wiringPiSetup();    
        
        
        while(i++ < numberOfPorts)
        {
            if(pinNumbers[i] && directions[i])
                pinMode(pinNumbers[i],directions[i]);
            
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
int actuator::pwm_Setup(uint8_t pinNumbers[],  uint8_t numberOfPorts)
{
    int result = 0;
    uint8_t i = 0;

    if(!pinNumbers || numberOfPorts >= MAX_PORTS_NUMBER )
    {
         cout << "Nullpointer for pinNumbers or too much number for ports bastard!? " << endl;
         result = 1;
    }
    else
    {
	uint8_t *temp = pinNumbers;
	printf("%p\n",temp);
        while(*temp)
	{
	    printf("%p\t%d\n",temp,temp[i]);
            i++;
	    temp++;

	}
	cout << i<<"/t" << numberOfPorts << endl;
        if(i != numberOfPorts)
          {
            result = 2;
            cout<< " not equal the given port numbers = " <<i<< "and the gpio numbers = "<<numberOfPorts << endl;
          }  
        
        i = 0;
        wiringPiSetup();

        while(i++ < numberOfPorts)
        {
            pinMode(pinNumbers[i],OUTPUT);
            digitalWrite(pinNumbers[i],LOW);
        }
    }

    return result;
}

void actuator::pwm_Write(uint8_t pinNumbers, uint16_t DC, unsigned int lengthOfDelay)
{
    if(DC >= MAX_DC)
        DC = MAX_DC -1;

    pwmWrite(pinNumbers,DC);
    delay(lengthOfDelay);

}