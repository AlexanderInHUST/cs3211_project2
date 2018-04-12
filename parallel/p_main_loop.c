//
// Created by 唐艺峰 on 2018/4/3.
//

#include "p_main_loop.h"

void p_start_simulation(region *region, input_data *input, int proc_id_x, int proc_id_y, int proc_id, int reg_sqrt_num,
                        MPI_Comm MPI_2D_COMM, MPI_Datatype MPI_PARTICLE, MPI_Datatype MPI_SIM_PARTICLE, char *file_name_prefix) {
    double time_step = input->time_step;
    int total_shots = input->time_slots;
    int horizon = input->horizon;
    double grid_size = input->grid_size;
    double total_energy = 0;
    double last_fast_velocity = 0;

    for (int step = 0; step < total_shots; step++) {

        ppm_image *image = p_create_ppm_image(region, proc_id_x, proc_id_y, reg_sqrt_num, MPI_2D_COMM, MPI_SIM_PARTICLE);
        char file_name[50];
        sprintf(file_name, "%s%d.ppm", file_name_prefix, step);
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
            memcpy(&all_sim_parts[proc_id][part_count - 1], sim_part, sizeof(simplified_part));
            free (sim_part);
        }

        MPI_Allgather(&particles_num, 1, MPI_INT, all_sim_num, 1, MPI_INT, MPI_2D_COMM);
        all_sim_num[proc_id] = particles_num;
        for (int bcast = 0; bcast < reg_sqrt_num * reg_sqrt_num; bcast++) {
            if (bcast != proc_id) {
                all_sim_parts[bcast] = (simplified_part *) malloc(sizeof(simplified_part) * all_sim_num[bcast]);
            }
            MPI_Bcast(all_sim_parts[bcast], all_sim_num[bcast], MPI_SIM_PARTICLE, bcast, MPI_2D_COMM);
        }

        for (int part_id = 0, part_count = 0; part_count < particles_num; part_id++) {
            if (region->is_occupied[part_id] == 0) {
                continue;
            }
            part_count++;

            particle *part = &region->particle_array[part_id];
            vector_pair *next_velocity = &part->next_velocity;
            double global_part_x = proc_id_x * grid_size + part->x;
            double global_part_y = proc_id_y * grid_size + part->y;
            for (int aim_reg_id = 0; aim_reg_id < reg_sqrt_num * reg_sqrt_num; aim_reg_id++) {
                int aim_parts_num = all_sim_num[aim_reg_id];
                int aim_regs_xy[2], aim_reg_x, aim_reg_y;
                MPI_Cart_coords(MPI_2D_COMM, aim_reg_id, 2, aim_regs_xy);
                aim_reg_x = aim_regs_xy[0];
                aim_reg_y = aim_regs_xy[1];

                for (int aim_part_id = 0; aim_part_id < aim_parts_num; aim_part_id++) {
                    simplified_part *aim_part = &all_sim_parts[aim_reg_id][aim_part_id];
                    particle *aim_whole_part = from_simplified_part(*aim_part);
                    gravitational_energy += compute_gravitational_energy(part, aim_whole_part, global_part_x
                        , global_part_y, aim_part->x, aim_part->y);

                    if (aim_reg_x >= reg_start_x && aim_reg_x <= reg_end_x &&
                            aim_reg_y >= reg_start_y && aim_reg_y <= reg_end_y) {
                        vector_pair *force = compute_gravitational_force(part, aim_whole_part, global_part_x
                                , global_part_y, aim_part->x, aim_part->y);
                        vector_pair *velocity_change = compute_velocity(part, force, time_step);
                        vector_pair_add(next_velocity, velocity_change);

                        free(force);
                        free(velocity_change);
                    }
                    free(aim_whole_part);
                }
            }

            kinetic_energy += compute_kinetic_energy(part);
            vector_pair *replacement = compute_displacement(part, time_step);
            part->next_x += replacement->to_north;
            part->next_y += replacement->to_east;
        }
        for (int i = 0; i < reg_sqrt_num * reg_sqrt_num; i++) {
            free (all_sim_parts[i]);
        }

        MPI_Allreduce(MPI_IN_PLACE, &gravitational_energy, 1, MPI_DOUBLE, MPI_SUM, MPI_2D_COMM);
        MPI_Allreduce(MPI_IN_PLACE, &kinetic_energy, 1, MPI_DOUBLE, MPI_SUM, MPI_2D_COMM);

        if (step == 0) {
            total_energy = gravitational_energy;
        }

        if (step % 20 == 0) {
            if (proc_id == 0) {
                printf("%d : %lf %lf\n", step, gravitational_energy, kinetic_energy);
            }
        }

        for (int part_id = 0, part_count = 0; part_count < particles_num; part_id++) {
            if (region->is_occupied[part_id] == 0) {
                continue;
            }
            part_count++;

            particle *part = &region->particle_array[part_id];
            correct_velocity(part, gravitational_energy, kinetic_energy, total_energy, last_fast_velocity);
            part->x = part->next_x;
            part->y = part->next_y;
            part->velocity.to_east = part->next_velocity.to_east;
            part->velocity.to_north = part->next_velocity.to_north;
        }

        particle *sent_parts[8], *recv_parts[8];
        int sent_parts_num[8] = {0}, recv_parts_num[8] = {0};
        for (int i = 0; i < 8; i++) {
            sent_parts[i] = (particle *) malloc(sizeof(particle) * particles_num);
        }

        last_fast_velocity = 0;
        for (int part_id = 0, part_count = 0; part_count < particles_num; part_id++) {
            if (region->is_occupied[part_id] == 0) {
                continue;
            }
            part_count++;

            particle *part = &region->particle_array[part_id];
            double part_v = sqrt(part->velocity.to_north * part->velocity.to_north
                                 + part->velocity.to_east * part->velocity.to_east);
            last_fast_velocity = MAX(part_v, last_fast_velocity);
            int is_load = p_load_sent_parts(sent_parts, sent_parts_num, part, proc_id_x, proc_id_y, reg_sqrt_num, grid_size);
            if (is_load == 1) {
                region->is_occupied[part_id] = 0;
                region->particles_num--;
            }
        }
        MPI_Allreduce(MPI_IN_PLACE, &last_fast_velocity, 1, MPI_DOUBLE, MPI_MAX, MPI_2D_COMM);
        p_swap_all_parts(sent_parts, sent_parts_num, recv_parts, recv_parts_num, proc_id_x, proc_id_y, reg_sqrt_num, MPI_2D_COMM, MPI_PARTICLE);
        p_save_recv_parts(region, recv_parts, recv_parts_num);

        for (int i = 0; i < 8; i++) {
            free (sent_parts[i]);
            if (recv_parts_num[i] != 0) {
                free(recv_parts[i]);
            }
        }
    }
}