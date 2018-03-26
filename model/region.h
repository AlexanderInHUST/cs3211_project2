//
// Created by 唐艺峰 on 2018/3/24.
//

#ifndef GALAXY_SIMULATION_REGION_H
#define GALAXY_SIMULATION_REGION_H

#include "../common.h"
#include "particle.h"
#include "../util/random.h"
#include "input_data.h"

#define DEFAULT_PART_ARRAY_LEN 2048
#define NOT_SMALL 1

typedef struct region {
    int pos_x;
    int pos_y;
    int particles_num;
    double grid_size;
    struct particle *particle_array;
} region;

void free_region(region **aim);

region *create_regions(input_data *input, int x, int y, int region_num);

void traverse_region(region *reg);

#endif //GALAXY_SIMULATION_REGION_H
