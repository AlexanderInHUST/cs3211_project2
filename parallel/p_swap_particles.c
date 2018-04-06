//
// Created by 唐艺峰 on 2018/4/3.
//

#include "p_swap_particles.h"

int p_load_sent_parts(particle **sent_parts, int *sent_parts_num, particle *part, int proc_id_x, int proc_id_y,
                       int region_sqt_num, int grid_size) {
    int at_edges = NO;
    if (proc_id_x != 0 && part->x < 0)                          at_edges |= UP;
    if (proc_id_x != region_sqt_num - 1 && part->x > grid_size) at_edges |= DOWN;
    if (proc_id_y != 0 && part->y < 0)                          at_edges |= LEFT;
    if (proc_id_y != region_sqt_num - 1 && part->y > grid_size) at_edges |= RIGHT;

    if (at_edges != NO) {
        int dir = magic_dir_map[at_edges];
        int current_num = sent_parts_num[dir];
        particle *aim_parts_array = sent_parts[dir];
        memcpy(&aim_parts_array[current_num], part, sizeof(particle));

        particle *modified_part = &aim_parts_array[current_num];
        switch (dir) {
            case 0: modified_part->x += grid_size; break;
            case 1: modified_part->x -= grid_size; break;
            case 2: modified_part->y += grid_size; break;
            case 3: modified_part->y -= grid_size; break;
            case 4: modified_part->x += grid_size; modified_part->y += grid_size; break;
            case 5: modified_part->x += grid_size; modified_part->y -= grid_size; break;
            case 6: modified_part->x -= grid_size; modified_part->y += grid_size; break;
            case 7: modified_part->x -= grid_size; modified_part->y -= grid_size; break;
            default: break;
        }
        modified_part->next_x = modified_part->x;
        modified_part->next_y = modified_part->y;
        sent_parts_num[dir]++;
        return 1;
    }
    return 0;
}

void p_swap_all_parts(particle **sent_parts, const int *sent_parts_num, particle **recv_parts, int *recv_parts_num,
                      int proc_id_x, int proc_id_y, int region_sqt_num, MPI_Comm MPI_2D_COMM, MPI_Datatype MPI_PARTICLE) {
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
            MPI_Sendrecv(&sent_parts_num[dir], 1, MPI_INT, send_proc_id, 0,
                         &recv_parts_num[dir], 1, MPI_INT, recv_proc_id, 0, MPI_2D_COMM, MPI_STATUS_IGNORE);
            recv_parts[dir] = (particle *) malloc(sizeof(particle) * recv_parts_num[dir]);
            MPI_Sendrecv(sent_parts[dir], sent_parts_num[dir], MPI_PARTICLE, send_proc_id, 1,
                         recv_parts[dir], recv_parts_num[dir], MPI_PARTICLE, recv_proc_id, 1, MPI_2D_COMM, MPI_STATUS_IGNORE);
        } else if (ok_to_send == 0 && ok_to_recv == 1) {
            MPI_Recv(&recv_parts_num[dir], 1, MPI_INT, recv_proc_id, 0, MPI_2D_COMM, MPI_STATUS_IGNORE);
            recv_parts[dir] = (particle *) malloc(sizeof(particle) * recv_parts_num[dir]);
            MPI_Recv(recv_parts[dir], recv_parts_num[dir], MPI_PARTICLE, recv_proc_id, 1, MPI_2D_COMM, MPI_STATUS_IGNORE);
        } else if (ok_to_send == 1 && ok_to_recv == 0) {
            MPI_Send(&sent_parts_num[dir], 1, MPI_INT, send_proc_id, 0, MPI_2D_COMM);
            MPI_Send(sent_parts[dir], sent_parts_num[dir], MPI_PARTICLE, send_proc_id, 1, MPI_2D_COMM);
        }
    }
}

void p_save_recv_parts(region *region, particle **recv_parts, const int *recv_parts_num) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < recv_parts_num[i]; j++) {
            enlarge_region(region);
            int recv_pos = find_first_available(region);
            region->particles_num++;
            region->is_occupied[recv_pos] = 1;
            memcpy(&region->particle_array[recv_pos], &recv_parts[i][j], sizeof(particle));
        }
    }
    shrink_region(region);
}