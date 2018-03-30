//
// Created by 唐艺峰 on 2018/3/24.
//

#include "region.h"

region *create_regions(input_data *input, int region_sqt_num) {

    int region_num = region_sqt_num * region_sqt_num;
    double grid_size = input->grid_size;
    int num_of_smalls = input->num_of_smalls;
    double small_mass = input->mass_of_smalls;
    double small_radius = input->radius_of_smalls;
    int num_of_bigs = input->num_of_bigs;
    char **bigs_data = input->bigs_data;
    region *regions = (region *) malloc(sizeof(region) * region_num);
    region *new_region = (region *) malloc(sizeof(region));

    new_region->grid_size = grid_size;
    new_region->particles_num = num_of_smalls + num_of_bigs;
    new_region->particle_array = (particle *) malloc
            (sizeof(particle) * MAX(DEFAULT_PART_ARRAY_LEN, new_region->particles_num * 2));
    for (int i = 0; i < num_of_smalls; i++) {
        load_particle(&new_region->particle_array[i], small_mass, small_radius,
                      next_double(grid_size), next_double(grid_size), (small_radius > NOT_SMALL) ? 0 : 1);
    }
    for (int i = 0; i < num_of_bigs; i++) {
        double radius, mass, pos_x, pos_y;
        sscanf(bigs_data[i], "%lf %lf %lf %lf", &radius, &mass, &pos_x, &pos_y);
        load_particle(&new_region->particle_array[i + num_of_smalls], mass, radius, pos_x, pos_y, 0);
    }
    for (int i = 0; i < region_num; i++) {
        region *current_reg = &regions[i];
        memcpy(current_reg, new_region, sizeof(region));
        current_reg->particle_array = (particle *) malloc
                (sizeof(particle) * MAX(DEFAULT_PART_ARRAY_LEN, new_region->particles_num * 2));
        memcpy(current_reg->particle_array, new_region->particle_array,
               sizeof(particle) * MAX(DEFAULT_PART_ARRAY_LEN, new_region->particles_num * 2));
        regions[i].pos_x = i / region_sqt_num;
        regions[i].pos_y = i % region_sqt_num;
    }
    free_region (&new_region);
    return regions;
}

void free_regions(region **aim, int num_sqt) {
    int num = num_sqt * num_sqt;
    for (int i = 0; i < num; i++) {
        region *cur = &(*aim)[i];
        free(cur->particle_array);
    }
    free (*aim);
}

void free_region(region **aim) {
    free((*aim)->particle_array);
    free(*aim);
}

void traverse_region(region *reg) {
    printf("The pos_x is %d and pox_y is %d\n", reg->pos_x, reg->pos_y);
    printf("The particles_num is %d\n", reg->particles_num);
    printf("The grid_size is %lf\n", reg->grid_size);
    for (int i = 0; i < reg->particles_num; i++) {
        particle *this = &reg->particle_array[i];
        printf("The %d particle is at (%lf, %lf) and has a radius of %lf mass of %lf and is_small = %d\n", i, this->x,
               this->y, this->radius, this->mass, this->is_small);
    }
}