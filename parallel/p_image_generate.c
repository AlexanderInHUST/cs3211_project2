//
// Created by 唐艺峰 on 2018/4/3.
//

#include "p_image_generate.h"

ppm_image *p_create_ppm_image(region *reg, int proc_id_x, int proc_id_y, int region_sqt_num, MPI_Comm MPI_2D_COMM, MPI_Datatype MPI_SIM_PARTICLE) {
    int grid_size = (int) reg->grid_size;
    ppm_image *image = (ppm_image *) malloc(sizeof(ppm_image));
    image->width = image->height = grid_size;
    image->data = (int *) malloc(sizeof(int *) * grid_size * grid_size * 3);
    memset(image->data, 0, sizeof(int *) * grid_size * grid_size * 3);

    simplified_part send_edge_parts[8][reg->particles_num];
    int send_edge_parts_num[8] = {0}; // UP DOWN LEFT RIGHT UL UR DL DR
    simplified_part *recv_edge_parts[8];
    int recv_edge_parts_num[8] = {0};

    for (int i = 0, part_count = 0; part_count < reg->particles_num; i++) {
        if(reg->is_occupied[i] == 0) {
            continue;
        }
        part_count++;

        particle *part = &reg->particle_array[i];
        paint_on_ppm(image, part, 0, 0);

        int at_edges = NO;
        if (proc_id_x != 0 && part->x - part->radius < 0)                          at_edges |= UP;
        if (proc_id_x != region_sqt_num - 1 && part->x + part->radius > grid_size) at_edges |= DOWN;
        if (proc_id_y != 0 && part->y - part->radius < 0)                          at_edges |= LEFT;
        if (proc_id_y != region_sqt_num - 1 && part->y + part->radius > grid_size) at_edges |= RIGHT;

        for (int j = 0; j < 3; j++) {
            int dir = magic_direction_map[at_edges][j];
            if (dir == -1) {
                break;
            }
            simplified_part *sim_part = from_part(*part);
            switch (dir) {
                case 0: sim_part->x += grid_size; break;
                case 1: sim_part->x -= grid_size; break;
                case 2: sim_part->y += grid_size; break;
                case 3: sim_part->y -= grid_size; break;
                case 4: sim_part->x += grid_size; sim_part->y += grid_size; break;
                case 5: sim_part->x += grid_size; sim_part->y -= grid_size; break;
                case 6: sim_part->x -= grid_size; sim_part->y += grid_size; break;
                case 7: sim_part->x -= grid_size; sim_part->y -= grid_size; break;
                default: break;
            }
            memcpy(&send_edge_parts[dir][send_edge_parts_num[dir]], sim_part, sizeof(particle));
            send_edge_parts_num[dir]++;
            free(sim_part);
        }
    }

    for (int dir = 0; dir < 8; dir++) {
        int move_x = 0, move_y = 0;
        switch (dir) {
            case 0: move_x = -1; move_y =  0; break;
            case 1: move_x = +1; move_y =  0; break;
            case 2: move_x =  0; move_y = -1; break;
            case 3: move_x =  0; move_y = +1; break;
            case 4: move_x = -1; move_y = -1; break;
            case 5: move_x = -1; move_y = +1; break;
            case 6: move_x = +1; move_y = -1; break;
            case 7: move_x = +1; move_y = +1; break;
            default: break;
        }
        int send_proc_id = 0, recv_proc_id = 0;
        int send_pos_x = proc_id_x + move_x;
        int send_pos_y = proc_id_y + move_y;
        int recv_pos_x = proc_id_x - move_x;
        int recv_pos_y = proc_id_y - move_y;
        int send_coords[2] = {send_pos_x, send_pos_y};
        int recv_coords[2] = {recv_pos_x, recv_pos_y};

        int ok_to_send = 1, ok_to_recv = 1;
        if (send_pos_x < 0 || send_pos_x > region_sqt_num - 1
            || send_pos_y < 0 || send_pos_y > region_sqt_num - 1) {
            ok_to_send = 0;
        } else {
            MPI_Cart_rank(MPI_2D_COMM, send_coords, &send_proc_id);
        }
        if (recv_pos_x < 0 || recv_pos_x > region_sqt_num - 1
            || recv_pos_y < 0 || recv_pos_y > region_sqt_num - 1) {
            ok_to_recv = 0;
        } else {
            MPI_Cart_rank(MPI_2D_COMM, recv_coords, &recv_proc_id);
        }

        if (ok_to_send == 1 && ok_to_recv == 1) {
            MPI_Sendrecv(&send_edge_parts_num[dir], 1, MPI_INT, send_proc_id, 0,
                         &recv_edge_parts_num[dir], 1, MPI_INT, recv_proc_id, 0, MPI_2D_COMM, MPI_STATUS_IGNORE);
            recv_edge_parts[dir] = (simplified_part *) malloc(sizeof(simplified_part) * recv_edge_parts_num[dir]);
            MPI_Sendrecv(send_edge_parts[dir], send_edge_parts_num[dir], MPI_SIM_PARTICLE, send_proc_id, 1,
                         recv_edge_parts[dir], recv_edge_parts_num[dir], MPI_SIM_PARTICLE, recv_proc_id, 1, MPI_2D_COMM, MPI_STATUS_IGNORE);
        } else if (ok_to_send == 0 && ok_to_recv == 1) {
            MPI_Recv(&recv_edge_parts_num[dir], 1, MPI_INT, recv_proc_id, 0, MPI_2D_COMM, MPI_STATUS_IGNORE);
            recv_edge_parts[dir] = (simplified_part *) malloc(sizeof(simplified_part) * recv_edge_parts_num[dir]);
            MPI_Recv(recv_edge_parts[dir], recv_edge_parts_num[dir], MPI_SIM_PARTICLE, recv_proc_id, 1, MPI_2D_COMM, MPI_STATUS_IGNORE);
        } else if (ok_to_send == 1 && ok_to_recv == 0) {
            MPI_Send(&send_edge_parts_num[dir], 1, MPI_INT, send_proc_id, 0, MPI_2D_COMM);
            MPI_Send(send_edge_parts[dir], send_edge_parts_num[dir], MPI_SIM_PARTICLE, send_proc_id, 1, MPI_2D_COMM);
        }
    }

    for (int i = 0; i < 8; i++) {
        int add_part_num = recv_edge_parts_num[i];
        simplified_part *add_parts = recv_edge_parts[i];
        for (int j = 0; j < add_part_num; j++) {
            simplified_part *sim_part = &add_parts[j];
            particle *part = from_simplified_part(*sim_part);
            paint_on_ppm(image, part, 0, 0);
            free(part);
        }
        if (add_part_num != 0) {
            free(add_parts);
        }
    }
    return image;
}