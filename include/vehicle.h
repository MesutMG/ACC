#ifndef VEHICLE_H
#define VEHICLE_H

#include <stdint.h>
#include "acc_types.h"

typedef struct {
    double velocity;   // m/s
    double mass;       // kg
    double throttle;   // 0-1 (%)

    double position;   // m
    double radar_front;

    uint8_t brake_pedal;      // 0-100%
    AccState_t state;  //OFF-SBY-ON 
    Acc_values acc_values;
} Vehicle_t;

#endif
