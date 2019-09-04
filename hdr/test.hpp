#ifndef _TEST_H_
#define _TEST_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

class foo
{
    public: 
    int i;
    foo();
    foo(int const i_);
    auto getFooInt(){ return i;}
};

class filehandler
{
    fstream fileHand;
    string patternFile;
    string lineFromFile;
    const string newFile= "usable.txt";
    vector<string> pattern;
    public:
    filehandler(const char &p): patternFile(&p) {};
    void getPatternFileName();
    void getInfoFromPattern();
    void getLinesFromVector();
    void processPattern();
    void FinishProcess();
};


#endif