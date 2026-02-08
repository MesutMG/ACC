#include "physics.h"
#include <math.h>


double calculate_drag(double velocity){

    return
    (0.5 * AIR_DENSITY * pow(velocity, 2) * AREA * DRAG_COEFF);
}

double calculate_friction(double mass){

    return
    (GRAVITY * mass * ROLLING_RESISTANCE);
}

double calculate_net_force(Vehicle_t *v){

    double net_force = ((ENGINE_FORCE_MAX * v->throttle)
                        - calculate_drag(v->velocity)
                        - calculate_friction(v->mass));

    if ((v->velocity > 0)){
        return(net_force);
    }

    else if ((v->velocity == 0) && (net_force > 0)){
        return (net_force);
    }

    return 0.0;
    //direction is stored independently, so no negative velocity
 
}

void physics_update(Vehicle_t *v, double dt){

    double net_force = calculate_net_force(v);

    double acceleration = net_force / v->mass;

    v->velocity = v->velocity + acceleration * dt;

    if (v->velocity < 0){
        v->velocity = 0;
    }

    v->position = v->position + v->velocity * dt; 

    return;
}