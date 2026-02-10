#include "acc_types.h"

void acc_update(Vehicle_t *v, AccInputs_t inputs, double dt) {
    
    //state machine
    switch (v->state) {
        case ACC_OFF:
            if (inputs.acc_on_switch) {
                v->state = ACC_STANDBY;
                v->throttle = 0.0;
            }
            break;

        case ACC_STANDBY:
            if (inputs.set_speed_switch){
                v->state = ACC_ACTIVE;
                v->target_speed = v->velocity;
            }
            break;

        case ACC_ACTIVE:

            if (inputs.brake_pedal > 0) {
                v->state = ACC_STANDBY;
                v->throttle = 0.0; // Let driver take over
            }
            
            else {

                if (inputs.radar_distance < 150){
                    v->throttle = 0.0;
                }
                
                else  {
                    v->throttle = (v->target_speed - v->velocity) ;//https://youtu.be/XVYRT0Mbu7A?t=194;
                }
                

                // Run Cruise Control Logic
                // If distance < 150, throttle = 0
                // Else, Simple P-Control: throttle = (target - current) * Kp
            }
            break;
    }
}