//
// Created by 唐艺峰 on 2018/4/3.
//

#ifndef GALAXY_SIMULATION_P_IMAGE_GENERATE_H
#define GALAXY_SIMULATION_P_IMAGE_GENERATE_H

#include "../common.h"
#include "../model/region.h"
#include "../model/ppm_image.h"
#include "../util/image_painter.h"

ppm_image * p_create_ppm_image(region * reg, int regs_num, int proc_id);

#endif //GALAXY_SIMULATION_P_IMAGE_GENERATE_H
