#include <stdio.h>
#include <acc_types.h>

acc_status_t update_vehicle_state(Vehicle_t *v, double time_step);
void physics_update(Vehicle_t *v, double dt);
void acc_update(Vehicle_t *v, AccInputs_t inputs, double dt);

int main(){

    Vehicle_t my_car;
    my_car.velocity = 0.0;
    my_car.mass = 1000.0;
    my_car.position = 0.0;
    my_car.throttle = 0.0;

    FILE *fpt;
    fpt = fopen("vehicle_status.csv", "w+");
    fprintf(fpt, "Velocity  Position    Throttle\n");
    fclose(fpt);

    fpt = fopen("vehicle_status.csv", "a+");


    //t = 0-10 ,    0.1 increase for presicion
    my_car.throttle = 0.5; //50%
    for (uint8_t i = 0; i < 100; i++)
    {
        physics_update(&my_car, 0.1);
        //dt in physics_update is deltatime, not total time

        fprintf(fpt, "%f    %f  %f\n",
        my_car.velocity, my_car.position, my_car.throttle);
    }
    //---------------------------------------------------------------
    AccInputs_t testinput = {1,100,0,130};

    for (uint8_t i = 0; i < 100; i++)
    {
        acc_update(&my_car,testinput,0.1);
    }

    /*
    //t = 10-20 ,   0.1 increase for presicion
    my_car.throttle = 0.0; //0%
    for (uint8_t i = 0; i < 100; i++)
    {
        physics_update(&my_car, 0.1);
        //dt in physics_update is deltatime, not total time

        fprintf(fpt, "%f    %f  %f\n",
        my_car.velocity, my_car.position, my_car.throttle);
    }*/
    fclose(fpt);
    
    

    return 0;
}


