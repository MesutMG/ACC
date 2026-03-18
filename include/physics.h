#ifndef PHYSICS_H
#define PHYSICS_H

#include "vehicle.h"

#define AIR_DENSITY 1.225f          //kg/m^3
#define DRAG_COEFF 0.3f             //aerodynamic drag (Cd)
#define AREA 2.5f                   //m^2 (frontal cut)
#define GRAVITY 9.81f               //m/s^2
#define ROLLING_RESISTANCE 0.015f   //road friction
#define ENGINE_FORCE_MAX 5000.0f    //5000N at 100% throttle - //move to the vehicle_t


double calculate_drag(double velocity);

double calculate_friction(double mass);

double get_acceleration(Vehicle_t *v, double test_velocity);

void acc_update(Vehicle_t *v, double dt);

void physics_update(Vehicle_t *v, double dt);

#endif
