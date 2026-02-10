#ifndef ACC_LOGIC_H
#define ACC_LOGIC_H

#include <stdint.h>

//off, standby, active, error
typedef enum {
    ACC_OFF,      // System disabled
    ACC_STANDBY,  // System enabled but not active (e.g., speed too low)
    ACC_ACTIVE,   // System controlling throttle/brakes
    ACC_ERROR     // Sensor failure or safety violation
} AccState_t;

//turn on, set speed, brake%, radar dist.
typedef struct {
    uint8_t acc_on_switch;    // 1 = Driver turned ACC ON
    uint8_t set_speed_switch; // 1 = Driver pressed "Set Speed"
    uint8_t brake_pedal;      // 0-100%
    double radar_distance;    // Distance to lead vehicle (m)
} AccInputs_t;

#endif
