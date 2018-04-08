//
// Created by 唐艺峰 on 2018/3/26.
//

#ifndef GALAXY_SIMULATION_PHYSICS_H
#define GALAXY_SIMULATION_PHYSICS_H

#include "../model/particle.h"
#include "../model/vector_pair.h"
#include "math.h"

#define G_CONST 6.67408
#define DISTANCE(x1, y1, x2, y2) sqrt((double)(((x1) - (x2)) * ((x1) - (x2)) + ((y1) - (y2)) * ((y1) - (y2))))

vector_pair *compute_gravitational_force(particle *a, particle *b, double ax, double ay, double bx, double by);
vector_pair *compute_displacement(particle *part, double time);
vector_pair *compute_velocity(particle *part, vector_pair *force, double time);
double compute_gravitational_energy(particle *a, particle *b, double ax, double ay, double bx, double by);
double compute_kinetic_energy(particle *a);
void correct_velocity(particle *a, double g_energy, double k_energy, double total_energy, double last_fast);

#endif //GALAXY_SIMULATION_PHYSICS_H
