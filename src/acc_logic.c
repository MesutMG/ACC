#include "acc_types.h"
#include "stdio.h"

double last_error = 0.0f;
double new_throttle;

void acc_update(Vehicle_t *v) {
    printf("-------\n");
    //state machine
    switch (v->state) {
        case ACC_OFF:
            printf("acc_off///\n");
            break;

        case ACC_STANDBY:
            printf("acc_standby///\n");
            if (v->inputs.set_speed_switch){
                v->state = ACC_ACTIVE;
                v->target_speed = v->inputs.set_speed_switch;
            }

        case ACC_ACTIVE:
            printf("acc_active///\n");
            if (v->inputs.brake_pedal > 0) {
                v->state = ACC_STANDBY;
                v->throttle = 0.0;
            } else {

                if (v->inputs.radar_distance < 150){
                    printf("radar distance low\n");
                    v->throttle = 0.0;
                }
                
                else  { 
                    if (KP * (v->target_speed - v->velocity) >= 1.0){
                        v->throttle = 1.0;
                    } else
                    {
                        last_error  = last_error + (KP / Ti) * (v->target_speed - v->velocity);
                        printf("error speed/// %f\n", (v->target_speed - v->velocity));
                        
                        new_throttle = KP * (v->target_speed - v->velocity) + last_error;

                        if (new_throttle >= 0.0 && new_throttle <= 1.0){
                            v->throttle = new_throttle;
                        } else if (new_throttle > 1.0) {
                            v->throttle = 1.0;
                        } else {
                            v->throttle = 0.0;
                        }
                        
                    }
                    
                    printf("throttle/// %f\n",v->throttle);
                }
                
            break;
    }
}
}

void acc_on_off(Vehicle_t *v){
    if (v->state == ACC_OFF){
        v->state = ACC_STANDBY;
    } else if ((v->state == ACC_STANDBY) || (v->state = ACC_ACTIVE)) {
        v->state = ACC_OFF; 
    }
    
}