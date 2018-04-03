//
// Created by 唐艺峰 on 2018/3/26.
//

#ifndef GALAXY_SIMULATION_S_MAIN_LOOP_H
#define GALAXY_SIMULATION_S_MAIN_LOOP_H

#include "../model/region.h"
#include "../util/physics.h"
#include "../util/file_helper.h"
#include "s_swap_particles.h"
#include "s_image_generate.h"

void s_start_simulation(region *regions, input_data *input, int num_of_regions);

#endif //GALAXY_SIMULATION_S_MAIN_LOOP_H
