#include "mainApp.h"

vector<unique_ptr<sensor>> Vec_Sensors;
vector<unique_ptr<actuator>> Vec_Actuators;
vector<unique_ptr<actuator>> Vec_SensActuators;

const string config = "./JSON/pattern/rand3.json";
// const string config = "./JSON/pattern/iso_4217.json";

using json = nlohmann::json;

MainApp::MainApp(const string& configFile)
{
    int logopt  = LOG_PID;
    const char* name ="RPI_IOT";
    #if DEBUG_LOG
        logopt  |= LOG_CONS | LOG_DEBUG /*| LOG_PERROR*/;
    #endif

    openlog(NULL,  logopt, LOG_LOCAL1);

    mConfig = configFile;
    std::ifstream f("./template.json");
    json data = json::parse(f);
    cout <<"Writing out json parse result start" <<endl;
    
    cout << data << endl;

    cout <<"Writing out json parse result finish" <<endl;

}


MainApp::MainApp() 
    : mConfig(config)
{
    int logopt  = LOG_PID;
    const char* name ="RPI_IOT";
    #if DEBUG_LOG
        logopt  |= LOG_CONS | LOG_DEBUG /*| LOG_PERROR*/;
    #endif

    openlog(NULL,  logopt, LOG_LOCAL1);
    mJson = make_unique<JsonComponent>();
    mJson->openJson();
    
}
