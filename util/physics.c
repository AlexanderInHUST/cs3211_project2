//
// Created by 唐艺峰 on 2018/3/26.
//

#include "physics.h"

vector_pair *compute_gravitational_force(particle *a, particle *b, double ax, double ay, double bx, double by) {
    vector_pair *pair = (vector_pair *) malloc(sizeof(vector_pair));
    double distance = DISTANCE(ax, ay, bx, by);
    if (distance < a->radius + b->radius) {
        pair->to_north = 0;
        pair->to_east = 0;
    } else {
        double force = G_CONST * a->mass * b->mass / (distance * distance);
        double sin_x = (by - ay) / distance;
        double cos_x = (bx - ax) / distance;
        pair->to_north = cos_x * force;
        pair->to_east = sin_x * force;
    }
    return pair;
}

vector_pair *compute_displacement(particle *part, double time) {
    vector_pair *pair = (vector_pair *) malloc(sizeof(vector_pair));
    vector_pair *velocity = &part->velocity;
    vector_pair *next_velocity = &part->next_velocity;
    pair->to_east = (velocity->to_east + next_velocity->to_east) * time / 2;
    pair->to_north = (velocity->to_north + next_velocity->to_north) * time / 2;
    return pair;
}

vector_pair *compute_velocity(particle *part, vector_pair *force, double time) {
    vector_pair *pair = (vector_pair *) malloc(sizeof(vector_pair));
    pair->to_east = force->to_east / part->mass * time;
    pair->to_north = force->to_north / part->mass * time;
    return pair;
}