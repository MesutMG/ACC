#ifndef ACC_LOGIC_H
#define ACC_LOGIC_H

#include <stdint.h>

#define KP 0.4f
#define Ti 6.0f

//off, standby, active
typedef enum {
    ACC_OFF,      //system disabled
    ACC_STANDBY,  //system enabled but not active (zb speed too low)
    ACC_ACTIVE    //system controlling throttle/brakes
} AccState_t;

//on/off, set speed, brake%, radar dist.
typedef struct {
    uint8_t set_speed_switch; //driver pressed "Set Speed"
    uint8_t brake_pedal;      // 0-100%
    double radar_distance;    //distance to lead vehicle (m)
} AccInputs_t;

#endif
