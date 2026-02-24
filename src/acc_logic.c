#include "acc_types.h"
#include "stdio.h"


double acc_active_pid(Vehicle_t *v, double dt) {
    
    if (dt <= 0.0){return 0.0;}

    double speed_error = v->acc_values.target_speed - v->velocity;

    //declare PID variables, and set using speed_error
    double proportional = speed_error;
    v->acc_values.integral_error += speed_error * dt;
    double derivative = (speed_error - v->acc_values.last_error) / dt;
    
    //assign boundaries for integral max
    if (v->acc_values.integral_error > integral_max) {v->acc_values.integral_error = integral_max;}
    else if (v->acc_values.integral_error < -integral_max) {v->acc_values.integral_error = -integral_max;}

    v->acc_values.last_error = speed_error;

    //pid output with constants
    double output = (Kp * proportional) + (Ki * v->acc_values.integral_error) + (Kd * derivative);

    //set max throttle values
    if (output > 1.0) {return 1.0;}
    else if (output < 0.0) {return 0.0;}
    
    return output;
}

void acc_update(Vehicle_t *v, double dt) {
    printf("-------\n");
    //state machine
    switch (v->state) {
        
        case ACC_OFF:
            printf("acc_off///\n");
            break;

        case ACC_STANDBY:
            printf("acc_standby///\n");
            break;
        
        case ACC_ACTIVE:
            printf("acc_active///\n");

            if (v->inputs.brake_pedal > 0) {
                v->state = ACC_STANDBY;
                v->throttle = 0.0; //letting the driver take control
                break;

            } else if ((v->inputs.radar_front < 150.0) && (v->inputs.radar_front > 0)){
                v->state = ACC_FOLLOW;
                break;
            
            } else if (v->inputs.radar_front >= 150.0){
                v->throttle = acc_active_pid(v, dt); 
                printf("throttle/// %f\n", v->throttle);
                break;
            
            } else {printf("hmm");break;}

        case ACC_FOLLOW:
            printf("acc-follow");
            double distance_error = v->inputs.radar_front - safe_following_distance;
            double follow_speed = distance_error * Kgap;
                    
            if (follow_speed < 0.0) follow_speed = 0.0; 
                    
            //target speed = lower
            if      (v->acc_values.target_speed < follow_speed){;}
            else if (follow_speed < v->acc_values.target_speed){v->acc_values.target_speed = follow_speed;}
                    
            printf("radar active - adjusting target speed to: %f\n", v->acc_values.target_speed);
            break;

    }
}


void acc_on_off(Vehicle_t *v){
    if (v->state == ACC_OFF){
        v->state = ACC_STANDBY;
    } else if ((v->state == ACC_STANDBY) || (v->state == ACC_ACTIVE)) {
        v->state = ACC_OFF; 
    }
    
}

void acc_set_speed(Vehicle_t *v, double set_speed){
    if ((v->state == ACC_STANDBY) || (v->state == ACC_ACTIVE)){
        v->state = ACC_ACTIVE;
        v->acc_values.target_speed = set_speed;
    }

    else if (v->state == ACC_OFF){
        return;
    }
}