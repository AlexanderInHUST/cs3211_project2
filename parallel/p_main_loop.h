//
// Created by 唐艺峰 on 2018/4/3.
//

#ifndef GALAXY_SIMULATION_P_MAIN_LOOP_H
#define GALAXY_SIMULATION_P_MAIN_LOOP_H

#include "../model/input_data.h"
#include "../model/region.h"
#include "../model/ppm_image.h"
#include "p_image_generate.h"
#include "p_image_store.h"
#include "../util/file_helper.h"
#include "p_swap_particles.h"

void p_start_simulation(region *region, input_data *input, int proc_id_x, int proc_id_y, int proc_id, int reg_sqrt_num,
                        MPI_Comm MPI_2D_COMM, MPI_Datatype MPI_PARTICLE, MPI_Datatype MPI_SIM_PARTICLE, char *file_name_prefix);

#endif //GALAXY_SIMULATION_P_MAIN_LOOP_H
