#include <iostream>
#include "hdr/test.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        filehandler fh( argv[1]);
        fh.getPatternFileName();
        fh.getInfoFromPattern();
        fh.getLinesFromVector();
        fh.processPattern();
        fh.FinishProcess();
    }


    return 0;
}