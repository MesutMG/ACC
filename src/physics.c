#include "physics.h"
#include <math.h>

double calculate_drag(double velocity){
    return
    (0.5 * AIR_DENSITY * pow(velocity,2) * AREA * DRAG_COEFF);
}

double calculate_friction(double mass){
    return
    (GRAVITY * mass * ROLLING_RESISTANCE);
}

void physics_update(Vehicle_t *v, double dt){

    double engine_force = ENGINE_FORCE_MAX * v->throttle;

    double net_force =
    (engine_force - calculate_drag(v->velocity) - calculate_friction(v->mass));

    if (net_force < 0){
        return(0);
    }

    double acceleration = net_force / v->mass;

    v->velocity = v->velocity + acceleration * dt;

    v->position = v->position + v->velocity * dt; 

    return(0);
}