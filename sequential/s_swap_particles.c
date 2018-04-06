//
// Created by 唐艺峰 on 2018/3/30.
//

#include "s_swap_particles.h"

void s_send_particle(region *des, region *src, int part_id) {
    src->is_occupied[part_id] = 0;
    src->particles_num--;
    particle *send_part = &src->particle_array[part_id];
    enlarge_region(des);
    int recv_pos = find_first_available(des);
    des->particles_num++;
    des->is_occupied[recv_pos] = 1;
    memcpy(&des->particle_array[recv_pos], send_part, sizeof(particle));
}

int s_test_part_pos(particle *part, int grid_size) {
    int next_region_direction = NO;
    if (part->x < 0) {
        next_region_direction |= UP;
    } else if (part->x > grid_size) {
        next_region_direction |= DOWN;
    }
    if (part->y < 0) {
        next_region_direction |= LEFT;
    } else if (part->y > grid_size) {
        next_region_direction |= RIGHT;
    }
    return next_region_direction;
}

void s_send_part_to_region(region *regions, int region_idx, int part_id, int region_sqt_num, int grid_size) {
    int region_x = region_idx / region_sqt_num;
    int region_y = region_idx % region_sqt_num;
    int move_x = 0;
    int move_y = 0;
    int direction = s_test_part_pos(&regions[region_idx].particle_array[part_id], grid_size);
    if ((direction & LEFT) != 0) {
        if (region_y != 0) {
            move_y = -1;
        }
    }
    if ((direction & RIGHT) != 0) {
        if (region_y != region_sqt_num - 1) {
            move_y = 1;
        }
    }
    if ((direction & UP) != 0) {
        if (region_x != 0) {
            move_x = -1;
        }
    }
    if ((direction & DOWN) != 0) {
        if (region_x != region_sqt_num - 1) {
            move_x = 1;
        }
    }
    int des_region_id = region_idx + move_y + region_sqt_num * move_x;
    particle *part = &regions[region_idx].particle_array[part_id];
    part->next_x = part->x = part->x - move_x * grid_size;
    part->next_y = part->y = part->y - move_y * grid_size;
    s_send_particle(&regions[des_region_id], &regions[region_idx], part_id);
}