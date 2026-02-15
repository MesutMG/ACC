#ifndef ACC_TYPES_H
#define ACC_TYPES_H

#include <stdint.h>
#include "acc_logic.h"

typedef struct {
    double velocity;   // m/s
    double position;   // m
    double mass;       // kg
    double throttle;   // 0-100%
    AccState_t state;  //OFF-SBY-ON 
    AccInputs_t inputs;//onoff-setspeed-brake-radar
    double target_speed;
} Vehicle_t;

#endif
