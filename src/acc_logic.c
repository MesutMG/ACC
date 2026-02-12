#include "acc_types.h"
#include "stdio.h"

void acc_update(Vehicle_t *v, AccInputs_t inputs) {
    printf("-------\n");
    //state machine
    switch (v->state) {
        case ACC_OFF:
            printf("acc_off///\n");
            if (inputs.acc_on_switch) {
                v->state = ACC_STANDBY;
                v->throttle = 0.0;
            }
            break;

        case ACC_STANDBY:
            printf("acc_standby///\n");
            if (inputs.set_speed_switch){
                v->state = ACC_ACTIVE;
                v->target_speed = inputs.set_speed_switch;
            }
            break;

        case ACC_ACTIVE:
            printf("acc_active///\n");
            if (inputs.brake_pedal > 0) {
                v->state = ACC_STANDBY;
                v->throttle = 0.0; // Let driver take over
            }
            
            else {

                if (inputs.radar_distance < 150){
                    printf("radar distance low\n");
                    v->throttle = 0.0;
                }
                
                else  { 
                    if (KP * (v->target_speed - v->velocity) >= 1.0){
                        v->throttle = 1.0;
                    } else
                    {
                        v->throttle = KP * (v->target_speed - v->velocity);
                    }
                    
                    printf("throttle %f\n",v->throttle); //----------------------------------------
                                /* + KP/ti * last_error_reset */;//PI control equation
                }
                
            break;
    }
}
}