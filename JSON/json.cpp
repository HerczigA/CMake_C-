#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include "json.hpp"



void json_herczig::json::getPatternFileName()
{
    cout << jsonFile << endl;
}

void json_herczig::json::getInfoFromPattern()
{
    try
    {
        fileHand.open(jsonFile.c_str(), ios::in);
        
    }
    catch(fstream::failure e)
    {
        std::cerr << e.what() << '\n';
        std::cout << e.what() << "Exception under opening" << endl;
        return;
    }
    while(getline(fileHand,lineFromFile))
        pattern.push_back(lineFromFile);

    fileHand.close();

}

void json_herczig::json::getLinesFromVector()
{
    for(auto x : pattern)
        cout << x << endl;
}

void json_herczig::json::processPattern()
{
  
    
    auto it = pattern.begin();
    while(it != pattern.end())
    {
        
        auto temp = pattern[0];
        if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (char c)
            {  return (c == '{' || c == '}' ); }   ))
            ;
        
        else if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (std::string str)
            {   return str == "Device"; }   ))
        this->deviceNumber++;   
        
        else if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (std::string str)
            {   return str == "devtype"; }   ))
        {
          size_t found = temp.find_last_of(":");
          size_t dev ;
          temp.erase(temp.begin() + 0, temp.begin() + found + 1); // second begin should be end.. then found  = find_end_if
          temp.erase(temp.begin() + temp.length());



          switch (temp) 
          {
            case "Sensor" :
                dev = 1;
                break;
            
            case "Actuator" :
                dev = 2;
                break;
            
            case "Sensor_Actuator" :
                dev = 3;
                break;
            
            default :
                dev = 4;
                break;
          }
          

          this->devicetype.push_back(dev);
        }
        
        else if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (std::string str)
            {   return str == "commtype"; }   ))
        {
            
        }
        else if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (std::string str)
            {   return str == "name"; }   ))
        {
            
        }
        
        else if( temp.end() != std::find_if(temp.begin(),temp.end(),[] (std::string str)
            {   return str == "ID"; }   ))
        {
            
        }

        it++;
        
        
    }
    

}


void json_herczig::json::FinishProcess()
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