//
// Created by 唐艺峰 on 2018/4/3.
//

#ifndef GALAXY_SIMULATION_P_IMAGE_STORE_H
#define GALAXY_SIMULATION_P_IMAGE_STORE_H

#include "../model/ppm_image.h"

void p_store_file (ppm_image * image, char * file_name, int proc_id, int region_sqt_num);

#endif //GALAXY_SIMULATION_P_IMAGE_STORE_H
