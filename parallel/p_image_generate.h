//
// Created by 唐艺峰 on 2018/4/3.
//

#ifndef GALAXY_SIMULATION_P_IMAGE_GENERATE_H
#define GALAXY_SIMULATION_P_IMAGE_GENERATE_H

#include "../common.h"
#include "../model/region.h"
#include "../model/ppm_image.h"
#include "../util/image_painter.h"

#define NO 0x0
#define UP 0x1
#define DOWN 0x2
#define LEFT 0x4
#define RIGHT 0x8

//int edge_parts_num[8] = {0}; // UP DOWN LEFT RIGHT UL UR DL DR

const static int magic_direction_map[11][3] = {
        {-1}, {0, -1, -1}, {1, -1, -1}, {-1},
        {2, -1, -1}, {0, 2, 4}, {1, 2, 6}, {-1},
        {3, -1, -1}, {0, 3, 5}, {1, 3, 7}
};

ppm_image * p_create_ppm_image(region * reg, int proc_id_x, int proc_id_y, int region_sqt_num, MPI_Comm MPI_2D_COMM, MPI_Datatype MPI_PARTICLE);

#endif //GALAXY_SIMULATION_P_IMAGE_GENERATE_H
