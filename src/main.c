#include <stdio.h>
#include "acc_logic.h"
#include "physics.h"
#include "vehicle.h"
#include "noise.h"

double TIME_PASSED = 0.0f;

int main(){

    Vehicle_t my_car = (Vehicle_t){
    .velocity = 0,
    .mass     = 1000,
    .throttle = 0,
    .brake    = 0,
    .position = 0,

    .inputs = (VehicleInputs_t){
        .throttle_pedal = 0,
        .brake_pedal    = 0,
        .clutch_pedal    = 0,

        .radar_front    = 0,
        .radar_rear     = 0
        };

    .acc_state = ACC_OFF;

    .acc_values = (Acc_values){
        .acc_throttle       = 0,
        .acc_brake          = 0,

        .integral_error     = 0,
         .last_error         = 0,

        .target_speed       = 0,
        .radar_speed        = 0,
        .last_radar_front   = 0
        };

    };


    Vehicle_t car_2 = (Vehicle_t){
    .velocity = 0,
    .mass     = 1000,
    .throttle = 0,
    .brake    = 0,
    .position = 300,

    .inputs = (VehicleInputs_t){
        .throttle_pedal = 0,
        .brake_pedal    = 0,
        .clutch_pedal    = 0,

        .radar_front    = 0,
        .radar_rear     = 0
        };

    .acc_state = ACC_OFF;

    .acc_values = (Acc_values){
        .acc_throttle       = 0,
        .acc_brake          = 0,

        .integral_error     = 0,
         .last_error         = 0,

        .target_speed       = 0,
        .radar_speed        = 0,
        .last_radar_front   = 0
        };

    };


    //radar info
    my_car.radar_front = (car_2.position - my_car.position) + (car_2.position - my_car.position) * noise_constant();


    FILE *fpt;
    fpt = fopen("../output/vehicle_status.csv", "w+");
    if (fpt == NULL){perror("file could not be opened"); return 1;}
    fprintf(fpt, "Velocity,Position,Throttle,Radar Front,State,Time,Velocity,Position,Throttle\n");

    //acc off, speeds up
    my_car.throttle = 0.3;
    car_2.throttle = 0.5;
    double time_step = 0.05f;

    for (uint32_t i = 0; i < 100; i++)
    { 
        acc_update(&my_car, time_step);
        physics_update(&my_car, time_step);
        physics_update(&car_2, time_step);

        //radar update
        my_car.acc_values.last_radar_front = my_car.radar_front;
        my_car.radar_front = (car_2.position - my_car.position) + (car_2.position - my_car.position) * noise_constant();;

        TIME_PASSED += time_step;

        fprintf(fpt, "%f,%f,%f,%f,%d,%f,%f,%f,%f\n",
        my_car.velocity, my_car.position, my_car.throttle, my_car.radar_front, my_car.acc_state, TIME_PASSED,
        car_2.velocity, car_2.position, car_2.throttle);
    }
 

    acc_on_off(&my_car);
    acc_set_speed(&my_car,80);

    for (uint32_t i = 0; i < 2500; i++)
    {
        acc_update(&my_car, time_step);
        physics_update(&my_car, time_step);
        physics_update(&car_2, time_step);

        //radar update
        my_car.acc_values.last_radar_front = my_car.radar_front;
        my_car.radar_front = (car_2.position - my_car.position) + (car_2.position - my_car.position) * noise_constant();;

        TIME_PASSED += time_step;

        fprintf(fpt, "%f,%f,%f,%f,%d,%f,%f,%f,%f\n",
        my_car.velocity, my_car.position, my_car.throttle, my_car.radar_front, my_car.acc_state, TIME_PASSED,
        car_2.velocity, car_2.position, car_2.throttle);
    }
/*
    car_2.throttle = 0.10;

        for (uint32_t i = 0; i < 100; i++)
    {
        physics_update(&my_car, time_step);
        physics_update(&car_2, time_step);

        //radar update
        my_car.acc_values.last_radar_front = my_car.radar_front;
        my_car.radar_front = (car_2.position - my_car.position) + (car_2.position - my_car.position) * noise_constant();;

        TIME_PASSED += 0.5;

        fprintf(fpt, "%f,%f,%f,%f,%d,%f,%f,%f,%f\n",
        my_car.velocity, my_car.position, my_car.throttle, my_car.radar_front, my_car.acc_state, TIME_PASSED,
        car_2.velocity, car_2.position, car_2.throttle);
    }

    car_2.throttle = 0.0;

        for (uint32_t i = 0; i < 100; i++)
    {
        physics_update(&my_car, time_step);
        physics_update(&car_2, time_step);

        //radar update
        my_car.acc_values.last_radar_front = my_car.radar_front;
        my_car.radar_front = 151;

        TIME_PASSED += 0.5;

        fprintf(fpt, "%f,%f,%f,%f,%d,%f,%f,%f,%f\n",
        my_car.velocity, my_car.position, my_car.throttle, my_car.radar_front, my_car.acc_state, TIME_PASSED,
        car_2.velocity, car_2.position, car_2.throttle);
    }
*/
    fclose(fpt);

    return 0;
}


