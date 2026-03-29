#ifndef VEHICLE_H
#define VEHICLE_H

#include <stdint.h>
#include "acc_types.h"

typedef struct {
    double throttle_pedal;
    double brake_pedal;
    double clutch_pedal; //for later updates --> transmission system

    double radar_front;
    double radar_rear;
} VehicleInputs_t;

typedef struct {
    double velocity;   // m/s
    double mass;       // kg
    double throttle;   // 0-1 (%)
    double brake;// 0-1 (%)

    double position;   // m
    
    AccState_t state;  //OFF-SBY-ON 
    AccValues_t acc_values;

    VehicleInputs_t inputs;

} Vehicle_t;

#endif
