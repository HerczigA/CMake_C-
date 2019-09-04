#include "../hdr/test.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <bits/stdc++.h>

using namespace std;

foo::foo()
{
    i = 10;
}


foo::foo(int const i_) : i{i_} {};



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
