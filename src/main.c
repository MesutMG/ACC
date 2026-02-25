#include <stdio.h>
#include <acc_types.h>

double TIME_PASSED = 0.0f;

void physics_update(Vehicle_t *v, double dt);
void acc_update(Vehicle_t *v);
void acc_on_off(Vehicle_t *v);
void acc_set_speed(Vehicle_t *v, double set_speed);

int main(){

    Vehicle_t my_car;
    my_car.velocity = 0.0;
    my_car.mass = 1000.0;
    my_car.position = 0.0;
    my_car.throttle = 0.0;
    my_car.state = ACC_OFF;
    my_car.inputs = (AccInputs_t){
    .brake_pedal = 0,
    .radar_front = 0.0
};

    Vehicle_t car_2;
    car_2.velocity = 50.0;
    car_2.mass = 1000.0;
    car_2.position = 100.0;
    car_2.throttle = 0.0;
    car_2.state = ACC_OFF;
    car_2.inputs = (AccInputs_t){
    .brake_pedal = 0,
    .radar_front = 0.0
};

    //set radar
    my_car.inputs.radar_front = car_2.position - my_car.position;


    FILE *fpt;
    fpt = fopen("../vehicle_status.csv", "w+");
    fprintf(fpt, "Velocity,Position,Throttle,Radar Front,State,Time,Velocity,Position,Throttle\n");
    fclose(fpt);

    fpt = fopen("../vehicle_status.csv", "a+");


    //acc off, speeds up
    my_car.throttle = 0.3;
    car_2.throttle = 0.3;
    double time_step = 0.05f;

    for (uint32_t i = 0; i < 100; i++)
    { 
        physics_update(&my_car, time_step);
        physics_update(&car_2, time_step);

        //radar update
        my_car.acc_values.last_radar_front = my_car.inputs.radar_front;
        my_car.inputs.radar_front = car_2.position - my_car.position;

        TIME_PASSED += time_step;

        fprintf(fpt, "%f,%f,%f,%f,%d,%f,%f,%f,%f\n",
        my_car.velocity, my_car.position, my_car.throttle, my_car.inputs.radar_front, my_car.state, TIME_PASSED,
        car_2.velocity, car_2.position, car_2.throttle);
    }
 

    acc_on_off(&my_car);
    acc_set_speed(&my_car,60);
    my_car.inputs = (AccInputs_t){0,(car_2.position - my_car.position)};

    for (uint32_t i = 0; i < 3000; i++)
    {
        physics_update(&my_car, time_step);
        physics_update(&car_2, time_step);

        //radar update
        my_car.acc_values.last_radar_front = my_car.inputs.radar_front;
        my_car.inputs.radar_front = car_2.position - my_car.position;

        TIME_PASSED += time_step;

        fprintf(fpt, "%f,%f,%f,%f,%d,%f,%f,%f,%f\n",
        my_car.velocity, my_car.position, my_car.throttle, my_car.inputs.radar_front, my_car.state, TIME_PASSED,
        car_2.velocity, car_2.position, car_2.throttle);
    }
/*
    car_2.throttle = 0.10;

        for (uint32_t i = 0; i < 100; i++)
    {
        physics_update(&my_car, time_step);
        physics_update(&car_2, time_step);

        //radar update
        my_car.acc_values.last_radar_front = my_car.inputs.radar_front;
        my_car.inputs.radar_front = car_2.position - my_car.position;

        TIME_PASSED += 0.5;

        fprintf(fpt, "%f,%f,%f,%f,%d,%f,%f,%f,%f\n",
        my_car.velocity, my_car.position, my_car.throttle, my_car.inputs.radar_front, my_car.state, TIME_PASSED,
        car_2.velocity, car_2.position, car_2.throttle);
    }

    car_2.throttle = 0.0;

        for (uint32_t i = 0; i < 100; i++)
    {
        physics_update(&my_car, time_step);
        physics_update(&car_2, time_step);

        //radar update
        my_car.acc_values.last_radar_front = my_car.inputs.radar_front;
        my_car.inputs.radar_front = 151;

        TIME_PASSED += 0.5;

        fprintf(fpt, "%f,%f,%f,%f,%d,%f,%f,%f,%f\n",
        my_car.velocity, my_car.position, my_car.throttle, my_car.inputs.radar_front, my_car.state, TIME_PASSED,
        car_2.velocity, car_2.position, car_2.throttle);
    }
*/
    fclose(fpt);

    return 0;
}


