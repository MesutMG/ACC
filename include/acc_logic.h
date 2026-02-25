#ifndef ACC_LOGIC_H
#define ACC_LOGIC_H

#include <stdint.h>

#define Kp 0.04775f
#define Ki 0.00677f
#define Kd 0.07f
#define integral_max 50.0f
#define Kgap 0.02f //for gap-closing
#define safe_following_distance 40.0f

//off, standby, active
typedef enum {
    ACC_OFF,      //system disabled
    ACC_STANDBY,  //system enabled but not active (zb speed too low)
    ACC_ACTIVE,    //system controlling throttle/brakes
    ACC_FOLLOW
} AccState_t;

typedef struct {
    double integral_error; //ACC PID
    double last_error; //ACC PID
    double target_speed;
    double radar_speed; //speed of the car front
    double last_radar_front;
} Acc_values;

//on/off, set speed, brake%, radar dist.
typedef struct {
    uint8_t brake_pedal;      // 0-100%
    double radar_front;    //distance to lead vehicle (m)
} AccInputs_t;

#endif
