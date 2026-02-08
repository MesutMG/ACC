#include <stdio.h>
#include <acc_types.h>

acc_status_t update_vehicle_state(Vehicle_t *v, double time_step);
void physics_update(Vehicle_t *v, double dt);

int main(){

    Vehicle_t my_car;
    my_car.velocity = 0.0;
    my_car.mass = 1000.0;
    my_car.position = 0.0;
    my_car.throttle = 0.0;

    //t = 0-10 ,    0.1 increase for presicion
    my_car.throttle = 0.5; //50%
    for (uint8_t i = 0; i < 100; i++)
    {
        physics_update(&my_car, i*0.1);
    }
    printf("\nVelocity at t=10: %f\nPosition at t=10: %f\n\n", my_car.velocity, my_car.position);

    //t = 10-20 ,   0.1 increase for presicion
    my_car.throttle = 0.0; //0%
    for (uint8_t i = 0; i < 100; i++)
    {
        physics_update(&my_car, i*0.1);
    }
    printf("Velocity at t=20: %f\nPosition at t=20: %f\n\n", my_car.velocity, my_car.position);
    

    return 0;
}


