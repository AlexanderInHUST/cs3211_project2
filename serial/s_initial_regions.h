//
// Created by 唐艺峰 on 2018/4/3.
//

#ifndef GALAXY_SIMULATION_S_INITIAL_REGIONS_H
#define GALAXY_SIMULATION_S_INITIAL_REGIONS_H

#include "../model/input_data.h"
#include "../model/region.h"
#include "../parallel/p_initial_regions.h"

void s_free_regions(region **aim, int num_sqt);
region *s_create_regions(input_data *input, int region_sqt_num);

#endif //GALAXY_SIMULATION_S_INITIAL_REGIONS_H
