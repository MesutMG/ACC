#include <stdio.h>
#include <acc_types.h>

void physics_update(Vehicle_t *v, double dt);
void acc_update(Vehicle_t *v);
void acc_on_off(Vehicle_t *v);

int main(){

    Vehicle_t my_car;
    my_car.velocity = 0.0;
    my_car.mass = 1000.0;
    my_car.position = 0.0;
    my_car.throttle = 0.0;
    my_car.state = ACC_OFF;

    my_car.inputs = (AccInputs_t){
    .set_speed_switch = 0,
    .brake_pedal = 0,
    .radar_distance = 0.0
};

    FILE *fpt;
    fpt = fopen("../vehicle_status.csv", "w+");
    fprintf(fpt, "Velocity,Position,Throttle\n");
    fclose(fpt);

    fpt = fopen("../vehicle_status.csv", "a+");

    //acc off, speeds up
    my_car.throttle = 0.5; //50%
    for (uint8_t i = 0; i < 20; i++)
    {
        physics_update(&my_car, 0.5);
        fprintf(fpt, "%f,%f,%f,%d\n",
        my_car.velocity, my_car.position, my_car.throttle,my_car.state);
    }
 
    acc_on_off(&my_car);
    my_car.inputs = (AccInputs_t){18,0,160};

    for (uint8_t i = 0; i < 100; i++)
    {
        physics_update(&my_car, 0.5);
        fprintf(fpt, "%f,%f,%f,%d\n",
        my_car.velocity, my_car.position, my_car.throttle, my_car.state);
    }

    fclose(fpt);

    return 0;
}


