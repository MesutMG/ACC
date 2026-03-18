#ifndef ACC_LOGIC_H
#define ACC_LOGIC_H

#include <stdint.h>
#include "vehicle.h"

#define Kp 0.04775f
#define Ki 0.00677f
#define Kd 0.07f
#define integral_max 50.0f
#define Kgap 0.02f //for gap-closing
#define safe_following_distance 40.0f

double acc_pid(Vehicle_t *v, double dt);

void acc_update(Vehicle_t *v, double dt);

void acc_on_off(Vehicle_t *v);

void acc_set_speed(Vehicle_t *v, double set_speed);

void find_follow_target_speed(Vehicle_t *v, double dt);

#endif
