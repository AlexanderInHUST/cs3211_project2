//
// Created by 唐艺峰 on 2018/3/24.
//

#ifndef GALAXY_SIMULATION_INPUT_HELPER_H
#define GALAXY_SIMULATION_INPUT_HELPER_H

#include "../common.h"

#define MAX_LINE_LEN 50

typedef struct input_data {
    int time_slots;
    double time_step;
    int horizon;
    int grid_size;
    int num_of_smalls;
    double mass_of_smalls;
    double radius_of_smalls;
    int num_of_bigs;
    char ** bigs_data;
} input_data;

input_data * load_file (char * file_name);
void free_input_data (input_data ** data);

#endif //GALAXY_SIMULATION_INPUT_HELPER_H
