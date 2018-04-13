//
// Created by 唐艺峰 on 2018/4/3.
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

const static int magic_dir_map[11] = {
        -1, 0, 1, -1,
        2, 4, 6, -1,
        3, 5, 7
};

int p_load_sent_parts(particle **sent_parts, int *sent_parts_num, particle *part, int proc_id_x, int proc_id_y,
                       int region_sqt_num, double grid_size);
void p_swap_all_parts(particle **sent_parts, const int *sent_parts_num, particle **recv_parts, int *recv_parts_num,
                      int proc_id_x, int proc_id_y, int region_sqt_num, MPI_Comm MPI_2D_COMM, MPI_Datatype MPI_PARTICLE);
void p_save_recv_parts(region *region, particle **recv_parts, const int *recv_parts_num);


#endif //GALAXY_SIMULATION_S_SWAP_PARTICLES_H
