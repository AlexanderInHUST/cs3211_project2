//
// Created by 唐艺峰 on 2018/3/26.
//

#include "s_main_loop.h"

void s_start_simulation(region *regions, input_data *input, int regs_sqt_num) {
    double time_step = input->time_step;
    int total_shots = input->time_slots;
    int horizon = input->horizon;
    int grid_size = input->grid_size;
    double total_energy = 0;

    for (int step = 0; step < total_shots; step++) {
        printf("step %d start.\n", step);

        ppm_image *image = s_create_ppm_image(regions, regs_sqt_num);
        char file_name[50];
        sprintf(file_name, "test%d.ppm", step);
        store_file(image, file_name);
        free_output_data(&image);

        double gravitational_energy = 0, kinetic_energy = 0;
        for (int reg_idx = 0; reg_idx < regs_sqt_num * regs_sqt_num; reg_idx++) {
            region *current_region = &regions[reg_idx];
            int reg_start_x = MAX(reg_idx / regs_sqt_num - horizon, 0);
            int reg_start_y = MAX(reg_idx % regs_sqt_num - horizon, 0);
            int reg_end_x = MIN(reg_idx / regs_sqt_num + horizon, regs_sqt_num - 1);
            int reg_end_y = MIN(reg_idx % regs_sqt_num + horizon, regs_sqt_num - 1);
            for (int part_id = 0, part_count = 0; part_count < current_region->particles_num; part_id++) {
                if (current_region->is_occupied[part_id] == 0) {
                    continue;
                }
                part_count++;
                particle *part = &current_region->particle_array[part_id];
                vector_pair *next_velocity = &part->next_velocity;
                double global_part_x = reg_idx / regs_sqt_num * grid_size + part->x;
                double global_part_y = reg_idx % regs_sqt_num * grid_size + part->y;
                for (int reg_idx_x = 0; reg_idx_x < regs_sqt_num; reg_idx_x++) {
                    for (int reg_idx_y = 0; reg_idx_y < regs_sqt_num; reg_idx_y++) {
                        region *aim_region = &regions[reg_idx_x * regs_sqt_num + reg_idx_y];
                        for (int aim_part_id = 0, aim_part_count = 0; aim_part_count < aim_region->particles_num; aim_part_id++) {
                            if (aim_region->is_occupied[aim_part_id] == 0) {
                                continue;
                            }
                            aim_part_count++;
                            particle *aim_part = &aim_region->particle_array[aim_part_id];
                            double global_aim_x = reg_idx_x * grid_size + aim_part->x;
                            double global_aim_y = reg_idx_y * grid_size + aim_part->y;
                            gravitational_energy += compute_gravitational_energy(part, aim_part, global_part_x
                                    , global_part_y, global_aim_x, global_aim_y);
                        }
                    }
                }

                for (int reg_idx_x = reg_start_x; reg_idx_x <= reg_end_x; reg_idx_x++) {
                    for (int reg_idx_y = reg_start_y; reg_idx_y <= reg_end_y; reg_idx_y++) {
                        region *aim_region = &regions[reg_idx_x * regs_sqt_num + reg_idx_y];
                        for (int aim_part_id = 0, aim_part_count = 0; aim_part_count < aim_region->particles_num; aim_part_id++) {
                            if (aim_region->is_occupied[aim_part_id] == 0) {
                                continue;
                            }
                            aim_part_count++;
                            particle *aim_part = &aim_region->particle_array[aim_part_id];
                            double global_aim_x = reg_idx_x * grid_size + aim_part->x;
                            double global_aim_y = reg_idx_y * grid_size + aim_part->y;
                            vector_pair *force = compute_gravitational_force(part, aim_part, global_part_x
                                    , global_part_y, global_aim_x, global_aim_y);
                            vector_pair *velocity_change = compute_velocity(part, force, time_step);
                            vector_pair_add(next_velocity, velocity_change);

                            free(force);
                            free(velocity_change);
                        }
                    }
                }

                kinetic_energy += compute_kinetic_energy(part);
                vector_pair *replacement = compute_displacement(part, time_step);
                part->next_x += replacement->to_north;
                part->next_y += replacement->to_east;

            }
        }

        if (step == 0) {
            total_energy = gravitational_energy;
        }

        for (int reg_idx = 0; reg_idx < regs_sqt_num * regs_sqt_num; reg_idx++) {
            region *current_region = &regions[reg_idx];
            for (int part_id = 0, part_count = 0; part_count < current_region->particles_num; part_id++) {
                if (current_region->is_occupied[part_id] == 0) {
                    continue;
                }
                part_count++;

                particle *part = &current_region->particle_array[part_id];
                correct_velocity(part, gravitational_energy, kinetic_energy, total_energy);
                part->x = part->next_x;
                part->y = part->next_y;
                part->velocity.to_east = part->next_velocity.to_east;
                part->velocity.to_north = part->next_velocity.to_north;
            }
        }


        for (int reg_idx = 0; reg_idx < regs_sqt_num * regs_sqt_num; reg_idx++) {
            region *current_region = &regions[reg_idx];
            int original_num = current_region->particles_num;
            for (int part_id = 0, part_count = 0; part_count < original_num; part_id++) {
                if (current_region->is_occupied[part_id] == 0) {
                    continue;
                }
                part_count++;
                s_send_part_to_region(regions, reg_idx, part_id, regs_sqt_num, grid_size);
            }
            shrink_region(current_region);
        }
    }
}