//
// Created by 唐艺峰 on 2018/3/24.
//

#include "particle.h"

void load_particle(particle *mem, double mass, double radius, double x, double y, int is_small) {
    particle *part = mem;
    part->x = x;
    part->y = y;
    part->next_x = x;
    part->next_y = y;
    part->mass = mass;
    part->radius = radius;
    part->velocity.to_east = 0;
    part->velocity.to_north = 0;
    part->next_velocity.to_east = 0;
    part->next_velocity.to_north = 0;
    part->is_small = is_small;
}

particle *from_simplified_part(simplified_part part) {
    particle *new = (particle *)malloc(sizeof(particle));
    load_particle(new, part.mass, part.radius, part.x, part.y, -1);
    return new;
}

simplified_part *from_part(particle part) {
    simplified_part *new = (simplified_part *)malloc(sizeof(simplified_part));
    new->x = part.x;
    new->y = part.y;
    new->mass = part.mass;
    new->radius = part.radius;
    return new;
}