#ifndef PHYSICS_H
#define PHYSICS_H

#include "acc_types.h"

#define AIR_DENSITY 1.225f          //kg/m^3
#define DRAG_COEFF 0.3f             //aerodynamic drag (Cd)
#define AREA 2.5f                   //m^2 (frontal cut)
#define GRAVITY 9.81f               //m/s^2
#define ROLLING_RESISTANCE 0.015f   //road friction
#define ENGINE_FORCE_MAX 5000.0f    //5000N at 100% throttle

/**
 * @brief Calculates aerodynamic drag force.
 * Formula: 0.5 * rho * Cd * A * v^2
 * @param velocity Current speed in m/s
 * @return Force in Newtons (always positive magnitude)
 */
double calculate_drag(double velocity);

/**
 * @brief Calculates rolling resistance.
 * Formula: mass * gravity * friction_coeff
 * @param mass Vehicle mass in kg
 * @return Force in Newtons
 */
double calculate_friction(double mass);

/**
 * @brief Main physics update loop (Euler Integration).
 * 1. Calculate Engine Force (Assume max force is 5000N at 100% throttle).
 * 2. Sum forces (Engine - Drag - Friction).
 * 3. Calculate Acceleration (F = ma).
 * 4. Update Velocity (v = v + a*dt).
 * 5. Update Position (x = x + v*dt).
 * * @param v Pointer to the vehicle struct (Input/Output)
 * @param dt Time step in seconds (e.g., 0.1)
 */
void physics_update(Vehicle_t *v, double dt);

#endif