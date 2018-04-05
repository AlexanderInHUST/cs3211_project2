//
// Created by 唐艺峰 on 2018/4/3.
//

#include "p_main_loop.h"

void p_start_simulation(region *region, input_data *input, int proc_id_x, int proc_id_y, int proc_id, int reg_sqrt_num,
                        MPI_Comm MPI_2D_COMM, MPI_Datatype MPI_PARTICLE) {
    double time_step = input->time_step;
    int total_shots = input->time_slots;
    int horizon = input->horizon;
    int grid_size = input->grid_size;
    double total_energy = 0;

    for (int step = 0; step < time_step; step++) {
        ppm_image *image = p_create_ppm_image(region, proc_id_x, proc_id_y, reg_sqrt_num, MPI_2D_COMM, MPI_PARTICLE);
        char file_name[50];
        sprintf(file_name, "test%d.ppm", step);
        p_store_file(image, file_name, proc_id, proc_id_x, proc_id_y, reg_sqrt_num);
        free_output_data(&image);
    }
}