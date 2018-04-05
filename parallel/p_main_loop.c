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

        double gravitational_energy = 0, kinetic_energy = 0;
        int reg_start_x = MAX(proc_id_x - horizon, 0);
        int reg_start_y = MAX(proc_id_y - horizon, 0);
        int reg_end_x = MIN(proc_id_x + horizon, reg_sqrt_num - 1);
        int reg_end_y = MIN(proc_id_y + horizon, reg_sqrt_num - 1);
        int particles_num = region->particles_num;
        int all_sim_num[reg_sqrt_num * reg_sqrt_num];
        memset(all_sim_num, 0, sizeof(int) * reg_sqrt_num * reg_sqrt_num);
        simplified_part *all_sim_parts[reg_sqrt_num * reg_sqrt_num];
        all_sim_parts[proc_id] = (simplified_part *) malloc(sizeof(simplified_part) * particles_num);

        for (int part_id = 0, part_count = 0; part_count < particles_num; part_id++) {
            if (region->is_occupied[part_id] == 0) {
                continue;
            }
            part_count++;
            particle *part = &region->particle_array[part_id];
            double global_part_x = proc_id_x * grid_size + part->x;
            double global_part_y = proc_id_y * grid_size + part->y;
            simplified_part *sim_part = from_part(*part);
            sim_part->x = global_part_x;
            sim_part->y = global_part_y;
            memcpy(&all_sim_parts[proc_id][part_id], sim_part, sizeof(simplified_part));
            free (sim_part);
        }
        all_sim_num[proc_id] = particles_num;
        for (int bcast = 0; bcast < reg_sqrt_num * reg_sqrt_num; bcast++) {
            MPI_Bcast(&all_sim_num[bcast], 1, MPI_INT, bcast, MPI_2D_COMM);
            if (bcast != proc_id) {
                all_sim_parts[bcast] = (simplified_part *) malloc(sizeof(simplified_part) * all_sim_num[bcast]);
            }
            MPI_Bcast(all_sim_parts[bcast], all_sim_num[bcast], MPI_PARTICLE, bcast, MPI_2D_COMM);
        }

        for (int part_id = 0, part_count = 0; part_count < particles_num; part_id++) {
            if (region->is_occupied[part_id] == 0) {
                continue;
            }
            part_count++;

            particle *part = &region->particle_array[part_id];
            double global_part_x = proc_id_x * grid_size + part->x;
            double global_part_y = proc_id_y * grid_size + part->y;

        }



        for (int i = 0; i < reg_sqrt_num * reg_sqrt_num; i++) {
            for (int j = 0; j < all_sim_num[i]; j++) {
                printf("id:%d %d:%lf %lf\n", proc_id, i, all_sim_parts[i][j].x, all_sim_parts[i][j].y);
            }
        }
    }


}