//
// Created by 唐艺峰 on 2018/4/3.
//

#ifndef GALAXY_SIMULATION_P_MAIN_LOOP_H
#define GALAXY_SIMULATION_P_MAIN_LOOP_H

#include "../model/input_data.h"
#include "../model/region.h"

void s_start_simulation(region *regions, input_data *input, int num_of_regions, MPI_Comm MPI_2D_COMM, MPI_Datatype MPI_PARTICLE);

#endif //GALAXY_SIMULATION_P_MAIN_LOOP_H
