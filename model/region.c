//
// Created by 唐艺峰 on 2018/3/24.
//


#include "region.h"

region * create_region (double grid_size, int num_of_smalls, double small_mass, double small_radius,
        int num_of_bigs, char ** bigs_data, int x, int y) {
    region * new_region = (region *) malloc(sizeof(region));
    new_region->grid_size = grid_size;
    new_region->particles_num = num_of_smalls + num_of_bigs;
    new_region->pos_x = x;
    new_region->pos_y = y;
    new_region->particle_array = (particle *) malloc
            (sizeof(particle) * MAX(DEFAULT_PART_ARRAY_LEN, new_region->particles_num * 2));

    for (int i = 0; i < num_of_smalls; i++) {
        particle * new_small = create_particle
                (small_mass, small_radius, next_double(grid_size), next_double(grid_size));
        memcpy (&new_region->particle_array[i], new_small, sizeof(particle));
        free (new_small);
    }

    for (int i = 0; i < num_of_bigs; i++) {
        double radius, mass, pos_x, pos_y;
        sscanf(bigs_data[i], "%lf %lf %lf %lf", &radius, &mass, &pos_x, &pos_y);
        particle * new_big = create_particle
                (mass, radius, pos_x, pos_y);
        memcpy (&new_region->particle_array[i + num_of_smalls], new_big, sizeof(particle));
        free (new_big);
    }

    return new_region;
}

void free_region (region ** aim) {
    free ((*aim)->particle_array);
    free (*aim);
}

void traverse_region(region * reg) {
    printf ("The pos_x is %d and pox_y is %d\n", reg->pos_x, reg->pos_y);
    printf ("The particles_num is %d\n", reg->particles_num);
    printf ("The grid_size is %lf\n", reg->grid_size);
    for (int i = 0; i < reg->particles_num; i++) {
        particle * this = &reg->particle_array[i];
        printf ("The %d particle is at (%lf, %lf) and has a radius of %lf mass of %lf\n"
                , i, this->x, this->y, this->radius, this->mass);
    }
}