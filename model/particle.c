//
// Created by 唐艺峰 on 2018/3/24.
//

#include "particle.h"

void load_particle(particle *mem, double mass, double radius, double x, double y, int is_small) {
    particle *part = mem;
    part->x = x;
    part->y = y;
    part->mass = mass;
    part->radius = radius;
    part->velocity.to_east = 0;
    part->velocity.to_north = 0;
    part->is_small = is_small;
}