//
// Created by 唐艺峰 on 2018/4/3.
//

#include "p_image_generate.h"

ppm_image *p_create_ppm_image(region *reg, int proc_id, int region_sqt_num) {
    int grid_size = (int) reg->grid_size;
    ppm_image *image = (ppm_image *) malloc(sizeof(ppm_image));
    image->width = image->height = grid_size;
    image->data = (int *) malloc(sizeof(int *) * grid_size * grid_size * 3);
    memset(image->data, 0, sizeof(int *) * grid_size * grid_size * 3);

    for (int j = 0; j < reg->particles_num; j++) {
        particle *part = &reg->particle_array[j];
        paint_on_ppm(image, part, 0, 0);
    }

//    int reg_pos_x = proc_id / region_sqt_num;
//    int reg_pos_y = proc_id % region_sqt_num;
//    int edge_num = 4;
//    if (reg_pos_x == 0) edge_num--;
//    if (reg_pos_x == region_sqt_num - 1) edge_num--;
//    if (reg_pos_y == 0) edge_num--;
//    if (reg_pos_y == region_sqt_num - 1) edge_num--;
//
//    for (int edge = 0; edge < edge_num; edge++) {
//
//    }

    return image;
}