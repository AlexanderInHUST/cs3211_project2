//
// Created by 唐艺峰 on 2018/3/26.
//

#ifndef GALAXY_SIMULATION_INPUT_DATA_H
#define GALAXY_SIMULATION_INPUT_DATA_H

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

#endif //GALAXY_SIMULATION_INPUT_DATA_H
