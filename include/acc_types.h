#ifndef ACC_TYPES_H
#define ACC_TYPES_H

#include <stdint.h>

typedef enum {
    ACC_OK = 0,
    ACC_ERROR = 1
} acc_status_t;

typedef struct {
    double velocity;   // m/s
    double position;   // m
    double mass;       // kg
    double throttle;   // 0-100%
} Vehicle_t;

#endif