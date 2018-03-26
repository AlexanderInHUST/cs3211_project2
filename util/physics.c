//
// Created by 唐艺峰 on 2018/3/26.
//

#include "physics.h"

vector_pair *gravitational_force(particle * a, particle * b) {
    vector_pair *pair = (vector_pair *) malloc(sizeof(vector_pair));
    double distance = DISTANCE(a->x, a->y, b->x, b->y);
    double force = G_CONST * a->mass * b->mass / (distance * distance);
    double sin_x = (b->y - a->y) / distance;
    double cos_x = (b->x - a->x) / distance;
    pair->to_north = sin_x * force;
    pair->to_east = cos_x * force;
    return pair;
}

vector_pair *displacement(particle *part, vector_pair *force, double time) {
    vector_pair *pair = (vector_pair *) malloc(sizeof(vector_pair));
    vector_pair *velocity = &part->velocity;
    pair->to_east = velocity->to_east * time + 0.5 * force->to_east / part->mass * time * time;
    pair->to_north = velocity->to_north * time + 0.5 * force->to_north / part->mass * time * time;
    return pair;
}

vector_pair *velocity(particle *part, vector_pair *force, double time) {
    vector_pair *pair = (vector_pair *) malloc(sizeof(vector_pair));
    vector_pair *velocity = &part->velocity;
    pair->to_east = velocity->to_east + force->to_east / part->mass * time;
    pair->to_north = velocity->to_north + force->to_north / part->mass * time;
    return pair;
}