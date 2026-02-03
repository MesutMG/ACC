#ifndef ACC_TYPES_H
#define ACC_TYPES_H

#include <stdint.h>

typedef enum {
    ACC_OK = 0,
    ACC_ERROR = 1
} acc_status_t;

typedef struct {
    double velocity;
    double position;
    double mass;
    double engine_force;
    uint8_t brake_pedal;

} Vehicle_t;

#endif