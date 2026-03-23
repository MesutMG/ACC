#ifndef ACC_TYPES_H
#define ACC_TYPES_H

#include <stdint.h>

typedef struct {
    double integral_error; //ACC PID
    double last_error; //ACC PID
    double target_speed;
    double radar_speed; //speed of the car front
    double last_radar_front;
    double last_set_speed;
    double acc_break;
} Acc_values;

//off, standby, active
typedef enum {
    ACC_OFF,      //system disabled
    ACC_STANDBY,  //system enabled but not active (zb speed too low)
    ACC_ACTIVE,    //system controlling throttle/brakes
    ACC_FOLLOW
} AccState_t;

#endif
