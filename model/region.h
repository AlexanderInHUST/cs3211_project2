//
// Created by 唐艺峰 on 2018/3/24.
//

#ifndef GALAXY_SIMULATION_REGION_H
#define GALAXY_SIMULATION_REGION_H

#include "../common.h"
#include "particle.h"
#include "../util/random.h"

#define DEFAULT_PART_ARRAY_LEN 2048
#define NOT_SMALL 1

typedef struct region {
    int pos_x;
    int pos_y;
    int particles_num;
    double grid_size;
    struct particle * particle_array;
} region;

void free_region (region ** aim);
region * create_region (double grid_size, int num_of_smalls, double small_mass, double small_radius,
                        int num_of_bigs, char ** bigs_data, int x, int y);
void traverse_region(region * reg);

#endif //GALAXY_SIMULATION_REGION_H
