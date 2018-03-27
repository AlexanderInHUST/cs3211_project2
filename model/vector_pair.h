//
// Created by 唐艺峰 on 2018/3/26.
//

#ifndef GALAXY_SIMULATION_VECTOR_PAIR_H
#define GALAXY_SIMULATION_VECTOR_PAIR_H

typedef struct vector_pair {
    double to_east;
    double to_north;
}vector_pair;

void vector_pair_add (vector_pair * a, vector_pair * b);

#endif //GALAXY_SIMULATION_VECTOR_PAIR_H
