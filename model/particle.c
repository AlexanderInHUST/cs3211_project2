//
// Created by 唐艺峰 on 2018/3/24.
//

#include "particle.h"

particle *create_particle(double mass, double radius, double x, double y) {
    particle *part = (particle *) malloc(sizeof(particle));
    part->x = x;
    part->y = y;
    part->mass = mass;
    part->radius = radius;
    part->velocity_east = 0;
    part->velocity_north = 0;
    return part;
}