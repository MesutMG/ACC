#include "acc_types.h"
#include "stdio.h"


double pid(Vehicle_t *v, double TIME_PASSED) {
    
    if (TIME_PASSED <= 0.0){return 0.0;}

    double error = v->target_speed - v->velocity;
    double proportional = error;

    v->integral_error += error * TIME_PASSED;

    double integral_max = 50.0; 
    if (v->integral_error > integral_max) {v->integral_error = integral_max;}

    else if (v->integral_error < -integral_max) {v->integral_error = -integral_max;}

    double derivative = (error - v->last_error) / TIME_PASSED;
    v->last_error = error;

    double output = (Kp * proportional) + (Ki * v->integral_error) + (Kd * derivative);

    if (output > 1.0) {return 1.0;}
    else if (output < 0.0) {return 0.0;}
    
    return output;
}

void acc_update(Vehicle_t *v, double TIME_PASSED) {
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
            } //NO BREAK! if the speed is set in the standby mode, it should be in the active mode immediately

        case ACC_ACTIVE:
            printf("acc_active///\n");
            if (v->inputs.brake_pedal > 0) {
                v->state = ACC_STANDBY;
                v->throttle = 0.0;
            } else {

                if (v->inputs.radar_front < 150){
                    printf("radar distance low\n");
                    v->throttle = 0.0;
                    v->state = ACC_STANDBY;
                }
                
                else { 
                    v->throttle = pid(v, TIME_PASSED); //controls the throttle
                    printf("throttle/// %f\n",v->throttle);
                }
                
            break;
            }
    }
}

void acc_on_off(Vehicle_t *v){
    if (v->state == ACC_OFF){
        v->state = ACC_STANDBY;
    } else if ((v->state == ACC_STANDBY) || (v->state == ACC_ACTIVE)) {
        v->state = ACC_OFF; 
    }
    
}
