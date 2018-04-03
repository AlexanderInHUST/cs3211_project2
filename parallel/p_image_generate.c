//
// Created by 唐艺峰 on 2018/4/3.
//

#include "p_image_generate.h"

ppm_image *p_create_ppm_image(region *reg) {
    int grid_size = (int) reg->grid_size;
    ppm_image *image = (ppm_image *) malloc(sizeof(ppm_image));
    image->width = image->height = grid_size;
    image->data = (int *) malloc(sizeof(int *) * grid_size * grid_size * 3);
    memset(image->data, 0, sizeof(int *) * grid_size * grid_size * 3);

    for (int j = 0; j < reg->particles_num; j++) {
        particle *part = &reg->particle_array[j];
        paint_on_ppm(image, part, 0, 0);
    }
    return image;
}