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

vector_pair *gravitational_force(particle * a, particle * b);
vector_pair *displacement(particle *part, vector_pair *force, double time);
vector_pair *velocity(particle *part, vector_pair *force, double time);

#endif //GALAXY_SIMULATION_PHYSICS_H
