#include "mainApp.h"

vector<unique_ptr<sensor>> Vec_Sensors;
vector<unique_ptr<actuator>> Vec_Actuators;
vector<unique_ptr<actuator>> Vec_SensActuators;


MainApp::MainApp()
{
    int logopt  = LOG_PID;
    const char* name ="RPI_IOT";
    #if DEBUG_LOG
        logopt  |= LOG_CONS | LOG_DEBUG /*| LOG_PERROR*/;
    #endif

    openlog(NULL,  logopt, LOG_LOCAL1);

}
