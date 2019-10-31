#ifndef _MAIN_INIT_HPP_
#define _MAIN_INIT_HPP_
#include <syslog.h>
#include <vector>
#include <memory>
#include "../hdr/device.hpp"

extern vector<unique_ptr<sensor>> Vec_Sensors;
extern vector<unique_ptr<actuator>> Vec_Actuators;
extern vector<unique_ptr<actuator>> Vec_SensActuators;


void InitBase();

#endif