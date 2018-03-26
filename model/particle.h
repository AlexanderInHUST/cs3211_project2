//
// Created by 唐艺峰 on 2018/3/24.
//

#ifndef GALAXY_SIMULATION_PARTICLE_H
#define GALAXY_SIMULATION_PARTICLE_H

#include "../common.h"

typedef struct particle {
    double x;
    double y;
    double mass;
    double radius;
    double velocity_north;
    double velocity_east;
    int is_small;
} particle;

void load_particle(particle *mem, double mass, double radius, double x, double y, int is_small);

#endif //GALAXY_SIMULATION_PARTICLE_H
