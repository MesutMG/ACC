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

double acc_pid(Vehicle_t *v, double dt);

void acc_update(Vehicle_t *v, double dt);

void acc_on_off(Vehicle_t *v);

void acc_set_speed(Vehicle_t *v, double set_speed);

void find_follow_target_speed(Vehicle_t *v, double dt);

#endif
