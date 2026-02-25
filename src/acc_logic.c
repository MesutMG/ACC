#include "acc_types.h"
#include "stdio.h"


double acc_pid(Vehicle_t *v, double dt) {
    
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

    double pid_result = (Kp * proportional) + (Ki * v->acc_values.integral_error) + (Kd * derivative);

    //set max throttle values
    if (pid_result > 1.0) {pid_result = 1;}
    else if (pid_result < 0.0) {pid_result = 0;}

    // using the older throttle so it doesn't jump --> eases the throttle
    double output = (v->throttle*0.8) + (pid_result*0.2);
    
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
                printf("breaked");
                break;

            } else if ((v->inputs.radar_front < 150.0) && (v->inputs.radar_front > 0)){
                v->state = ACC_FOLLOW;
                printf("radar lower than 15, activating follow");
                break;
            
            } else if (v->inputs.radar_front >= 150.0){
                v->throttle = acc_pid(v, dt); 
                printf("throttle/// %f\n", v->throttle);
                break;
            
            } else {printf("hmm");break;}

        case ACC_FOLLOW:
            printf("acc_follow///\n");

            if (v->inputs.brake_pedal > 0) {
                v->state = ACC_STANDBY;
                v->throttle = 0.0; //letting the driver take control
                printf("breaked");
                break;

            } else if (v->inputs.radar_front >= 150.0){
                v->state = ACC_ACTIVE;
                printf("acc is turning on");
                break;
            } else {
            find_follow_target_speed(v, dt);
            
            v->throttle = acc_pid(v, dt);

            printf("radar active - adjusting target speed to: %f\n", v->acc_values.target_speed);
            
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


void acc_set_speed(Vehicle_t *v, double set_speed){
    if ((v->state == ACC_STANDBY) || (v->state == ACC_ACTIVE)){
        v->state = ACC_ACTIVE;
        v->acc_values.target_speed = set_speed;
    }

    else if (v->state == ACC_OFF){
        return;
    }
}


void find_follow_target_speed(Vehicle_t *v, double dt){
    v->acc_values.radar_speed = v->velocity - ((v->acc_values.last_radar_front - v->inputs.radar_front) / dt);
    
    //set the target speed to lower one (speed of car in front or the ACC set speed)
    if (v->acc_values.radar_speed < v->acc_values.target_speed){v->acc_values.target_speed = v->acc_values.radar_speed;}
    printf("\nfinding target_speed: %f",v->acc_values.target_speed);
}
