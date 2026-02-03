#include <stdio.h>
#include <acc_types.h>

acc_status_t update_vehicle_state(Vehicle_t *v, double time_step);

int main(){

    Vehicle_t my_car;
    my_car.velocity = 10.0;
    my_car.mass = 1200.0;
    my_car.position = 0.0;

    printf("Initial speed: %.2f m/s\n", my_car.velocity);


    update_vehicle_state(&my_car, 0.1);
    printf("Speed after update: %.2f m/s\n", my_car.velocity);
    
    
    return 0;
}

acc_status_t update_vehicle_state(Vehicle_t *v, double time_step){
    if (v == NULL){
        return ACC_ERROR; //safety check to the pointer
    }

    v->velocity = v->velocity * 0.99;

    v->position = v->position + (v->velocity * time_step);

    return ACC_OK;
}
