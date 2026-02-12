#include <stdio.h>
#include <acc_types.h>

acc_status_t update_vehicle_state(Vehicle_t *v, double time_step);
void physics_update(Vehicle_t *v, double dt);
void acc_update(Vehicle_t *v, AccInputs_t inputs);

int main(){

    Vehicle_t my_car;
    my_car.velocity = 0.0;
    my_car.mass = 1000.0;
    my_car.position = 0.0;
    my_car.throttle = 0.0;
    my_car.state = ACC_OFF;

    FILE *fpt;
    fpt = fopen("../vehicle_status.csv", "w+");
    fprintf(fpt, "Velocity,Position,Throttle\n");
    fclose(fpt);

    fpt = fopen("../vehicle_status.csv", "a+");


    my_car.throttle = 0.5; //50%
    for (uint8_t i = 0; i < 20; i++)
    {
        physics_update(&my_car, 0.5);
        //dt in seconds

        fprintf(fpt, "%f,%f,%f\n",
        my_car.velocity, my_car.position, my_car.throttle);
    }
 
    
    AccInputs_t testinput = {1,40,0,160};

    for (uint8_t i = 0; i < 20; i++)
    {
        acc_update(&my_car,testinput);
        physics_update(&my_car, 0.5);
        fprintf(fpt, "%f,%f,%f,%d\n",
        my_car.velocity, my_car.position, my_car.throttle, my_car.state);
    }

    fclose(fpt);
    
    

    return 0;
}


