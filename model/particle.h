//
// Created by 唐艺峰 on 2018/3/24.
//

#ifndef GALAXY_SIMULATION_PARTICLE_H
#define GALAXY_SIMULATION_PARTICLE_H

#include "../common.h"
#include "vector_pair.h"

typedef struct particle {
    double x, y;
    double next_x, next_y;
    double mass;
    double radius;
    vector_pair velocity, next_velocity;
    int is_small;
} particle;

void load_particle(particle *mem, double mass, double radius, double x, double y, int is_small);

#endif //GALAXY_SIMULATION_PARTICLE_H
