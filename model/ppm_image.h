//
// Created by 唐艺峰 on 2018/3/26.
//

#include "region.h"

#ifndef GALAXY_SIMULATION_PPM_IMAGE_H
#define GALAXY_SIMULATION_PPM_IMAGE_H

#include "../common.h"

typedef struct ppm_image {
    int width;
    int height;
    int * data;
}ppm_image;

#endif //GALAXY_SIMULATION_PPM_IMAGE_H
