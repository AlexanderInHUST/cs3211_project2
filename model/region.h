//
// Created by 唐艺峰 on 2018/3/24.
//

#ifndef GALAXY_SIMULATION_REGION_H
#define GALAXY_SIMULATION_REGION_H

#include "../common.h"
#include "particle.h"
#include "../util/random.h"
#include "input_data.h"

#define NOT_SMALL 1

typedef struct region {
    int pos_x;
    int pos_y;
    int particles_num;
    int array_length;
    double grid_size;
    struct particle *particle_array;
    int *is_occupied;
} region;

void free_region(region **aim);

void traverse_region(region *reg);
int find_first_available(region *aim);
void shrink_region(region *aim);
void enlarge_region(region *aim);

#endif //GALAXY_SIMULATION_REGION_H
