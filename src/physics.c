#include "physics.h"

double calculate_drag(double velocity){

    return
    (0.5 * AIR_DENSITY * velocity * velocity * AREA * DRAG_COEFF);
}

double calculate_friction(double mass){

    return
    (GRAVITY * mass * ROLLING_RESISTANCE);
}

double get_acceleration(Vehicle_t *v, double test_velocity){
    double drag = calculate_drag(test_velocity);

    double friction = calculate_friction(v->mass);

    double engine_force = ENGINE_FORCE_MAX * v->throttle;

    double net_force = engine_force - drag - friction;

    if ((test_velocity <= 0.0) && (net_force < 0.0)){
        return 0.0;
    }

    return (net_force / v->mass);
}

void physics_update(Vehicle_t *v, double dt){

    double v_current = v->velocity;

    //RK4 approximation
    double k1_v = get_acceleration(v, v_current) * dt;
    double k1_p = v_current * dt;

    double k2_v = get_acceleration(v, (v_current + k1_v/2.0)) * dt;
    double k2_p = (v_current + k1_v/2.0) * dt;
    
    double k3_v = get_acceleration(v, (v_current + k2_v/2.0)) * dt;
    double k3_p = (v_current + k2_v/2.0) * dt;
    
    double k4_v = get_acceleration(v, (v_current + k3_v)) * dt;
    double k4_p = (v_current + k3_v) * dt;

    v->velocity = v_current + (k1_v + (2.0*k2_v) + (2.0*k3_v) + k4_v) / 6.0;
    v->position = v->position + (k1_p + (2.0*k2_p) + (2.0*k3_p) + k4_p) / 6.0;
    
    if (v->velocity < 0.0){
        v->velocity = 0.0;
    }

    return;
}
