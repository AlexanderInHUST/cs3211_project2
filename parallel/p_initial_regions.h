//
// Created by 唐艺峰 on 2018/4/3.
//

#ifndef GALAXY_SIMULATION_P_INITIAL_REGIONS_H
#define GALAXY_SIMULATION_P_INITIAL_REGIONS_H

#include "../model/input_data.h"
#include "../model/region.h"

void free_region(region **aim);
region *p_create_regions(input_data *input, int proc_id, int region_sqt_num);

#endif //GALAXY_SIMULATION_P_INITIAL_REGIONS_H
