#include "main_Init.hpp"
#include "../hdr/device.hpp"
#define DEBUG_LOG 1 


vector<unique_ptr<sensor>> Vec_Sensors;
vector<unique_ptr<actuator>> Vec_Actuators;
vector<unique_ptr<actuator>> Vec_SensActuators;

void InitBase()
{

    int logopt  = LOG_PID;
    const char* name ="RPI_IOT";
    #if DEBUG_LOG
        logopt  |= LOG_CONS | LOG_DEBUG /*| LOG_PERROR*/;
    #endif

    openlog(NULL,  logopt, LOG_LOCAL1);
    wiringPiSetup();

}