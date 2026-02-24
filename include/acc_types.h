#ifndef ACC_TYPES_H
#define ACC_TYPES_H

#include <stdint.h>
#include "acc_logic.h"

typedef struct {
    double velocity;   // m/s
    double position;   // m
    double mass;       // kg
    double throttle;   // 0-100%
    Acc_values acc_values;
    AccState_t state;  //OFF-SBY-ON 
    AccInputs_t inputs;//onoff-setspeed-brake-radar
} Vehicle_t;

#endif
