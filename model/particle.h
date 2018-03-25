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
} particle;

particle *create_particle(double mass, double radius, double x, double y);

#endif //GALAXY_SIMULATION_PARTICLE_H
