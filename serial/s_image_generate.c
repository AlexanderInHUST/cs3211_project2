//
// Created by 唐艺峰 on 2018/3/26.
//

#include "s_image_generate.h"

ppm_image *s_create_ppm_image(region *reg, int regs_sqt_num) {
    int grid_size = (int) reg[0].grid_size;
    ppm_image *image = (ppm_image *) malloc(sizeof(ppm_image));
    image->width = image->height = grid_size * regs_sqt_num;
    image->data = (int *) malloc(sizeof(int *) * regs_sqt_num * regs_sqt_num * grid_size * grid_size * 3);
    memset(image->data, 0, sizeof(int *) * regs_sqt_num * regs_sqt_num * grid_size * grid_size * 3);

    for (int i = 0; i < regs_sqt_num * regs_sqt_num; i++) {
        for (int j = 0; j < reg[i].particles_num; j++) {
            particle *part = &reg[i].particle_array[j];
            paint_on_ppm(image, part, i / regs_sqt_num, i % regs_sqt_num);
        }
    }
    return image;
}