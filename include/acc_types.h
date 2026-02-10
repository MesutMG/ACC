#ifndef ACC_TYPES_H
#define ACC_TYPES_H

#include <stdint.h>
#include "acc_logic.h"

typedef enum {
    ACC_OK = 0,
    ACC_ERROR = 1
} acc_status_t;

typedef struct {
    double velocity;   // m/s
    double position;   // m
    double mass;       // kg
    double throttle;   // 0-100%
    AccState_t state;  //acc_logic.h  
    double target_speed;
} Vehicle_t;

#endif
