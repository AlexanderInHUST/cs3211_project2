//
// Created by 唐艺峰 on 2018/3/24.
//

#ifndef GALAXY_SIMULATION_INPUT_HELPER_H
#define GALAXY_SIMULATION_INPUT_HELPER_H

#include "../common.h"
#include "../model/ppm_image.h"
#include "../model/input_data.h"

#define MAX_LINE_LEN 50

input_data * load_file (char * file_name);
void free_input_data (input_data ** data);
void store_file (ppm_image * image, char * file_name);
void free_output_data (ppm_image ** image);

#endif //GALAXY_SIMULATION_INPUT_HELPER_H
