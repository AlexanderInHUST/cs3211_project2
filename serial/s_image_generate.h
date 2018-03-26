//
// Created by 唐艺峰 on 2018/3/26.
//

#ifndef GALAXY_SIMULATION_S_IMAGE_GENERATE_H
#define GALAXY_SIMULATION_S_IMAGE_GENERATE_H

#include "../common.h"
#include "../model/region.h"
#include "../model/ppm_image.h"
#include "../util/image_painter.h"

ppm_image * s_create_ppm_image(region * reg, int regs_num);

#endif //GALAXY_SIMULATION_S_IMAGE_GENERATE_H
