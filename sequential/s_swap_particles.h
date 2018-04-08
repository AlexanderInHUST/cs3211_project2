//
// Created by 唐艺峰 on 2018/3/30.
//

#ifndef GALAXY_SIMULATION_S_SWAP_PARTICLES_H
#define GALAXY_SIMULATION_S_SWAP_PARTICLES_H

#include "../model/particle.h"
#include "../model/region.h"

#define NO 0x0
#define UP 0x1
#define DOWN 0x2
#define LEFT 0x4
#define RIGHT 0x8

void s_send_particle(region *des, region *src, int part_id);
int s_test_part_pos(particle *part, double grid_size);
void s_send_part_to_region(region *regions, int region_idx, int part_id, int region_sqt_num, double grid_size);

#endif //GALAXY_SIMULATION_S_SWAP_PARTICLES_H
