//
// Created by 唐艺峰 on 2018/3/24.
//

#include "region.h"

void traverse_region(region *reg) {
    printf("The pos_x is %d and pox_y is %d\n", reg->pos_x, reg->pos_y);
    printf("The particles_num is %d\n", reg->particles_num);
    printf("The grid_size is %lf\n", reg->grid_size);
    for (int i = 0; i < reg->particles_num; i++) {
        particle *this = &reg->particle_array[i];
        printf("The %d particle is at (%lf, %lf) and has a radius of %lf mass of %lf and is_occupied = %d\n", i, this->x,
               this->y, this->radius, this->mass, reg->is_occupied[i]);
    }
}

int find_first_available(region *aim) {
    int available_pos = -1;
    for (int i = 0; i < aim->array_length; i++) {
        if (aim->is_occupied[i] == 0) {
            available_pos = i;
            break;
        }
    }
    return available_pos;
}

void shrink_region(region *aim) {
    if (aim->particles_num < aim->array_length / 4) {
        int len = MAX(aim->array_length / 2, 2);
        particle *temp_particles = (particle *) malloc (sizeof(particle) * len);
        int *temp_occupied = (int *) malloc (sizeof(int) * len);
        memset(temp_occupied, 0, sizeof(int) * len);
        int pos = 0;
        for (int i = 0; pos < aim->particles_num; i++) {
            if (aim->is_occupied[i] == 1) {
                memcpy(&temp_particles[pos], &aim->particle_array[i], sizeof(particle));
                temp_occupied[pos] = 1;
                pos++;
            }
        }
        free(aim->particle_array);
        free(aim->is_occupied);
        aim->particle_array = temp_particles;
        aim->is_occupied = temp_occupied;
        aim->array_length = len;
    }
}

void enlarge_region(region *aim) {
    if (aim->particles_num >= aim->array_length) {
        aim->is_occupied = realloc(aim->is_occupied, sizeof(int) * aim->array_length * 2);
        memset(&aim->is_occupied[aim->array_length], 0, sizeof(int) * aim->array_length);
        aim->particle_array = realloc(aim->particle_array, sizeof(particle) * aim->array_length * 2);
        aim->array_length *= 2;
    }
}