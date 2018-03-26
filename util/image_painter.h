//
// Created by 唐艺峰 on 2018/3/26.
//

#ifndef GALAXY_SIMULATION_IMAGE_PAINTER_H
#define GALAXY_SIMULATION_IMAGE_PAINTER_H

#include "../model/particle.h"
#include "../model/ppm_image.h"

void paint_on_ppm(ppm_image *image, particle *part, int x_offset, int y_offset);
void traverse_image (ppm_image * image);

#endif //GALAXY_SIMULATION_IMAGE_PAINTER_H
