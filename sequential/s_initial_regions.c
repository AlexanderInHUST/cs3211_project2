//
// Created by 唐艺峰 on 2018/4/3.
//

#include "s_initial_regions.h"

region *s_create_regions(input_data *input, int region_sqt_num) {
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
    new_region->array_length = new_region->particles_num * 2;
    new_region->particle_array = (particle *) malloc (sizeof(particle) * new_region->array_length);
    new_region->is_occupied = (int *) malloc (sizeof(int) * new_region->array_length);
    memset(new_region->is_occupied, 0, sizeof(int) * new_region->array_length);

    for (int i = 0; i < num_of_smalls; i++) {
        load_particle(&new_region->particle_array[i], small_mass, small_radius,
                      next_double(grid_size), next_double(grid_size), (small_radius > NOT_SMALL) ? 0 : 1);
        new_region->is_occupied[i] = 1;
    }
    for (int i = 0; i < num_of_bigs; i++) {
        double radius, mass, pos_x, pos_y;
        sscanf(bigs_data[i], "%lf %lf %lf %lf", &radius, &mass, &pos_x, &pos_y);
        load_particle(&new_region->particle_array[i + num_of_smalls], mass, radius, pos_x, pos_y, 0);
        new_region->is_occupied[i + num_of_smalls] = 1;
    }

    for (int i = 0; i < region_num; i++) {
        region *current_reg = &regions[i];
        memcpy(current_reg, new_region, sizeof(region));
        current_reg->particle_array = (particle *) malloc (sizeof(particle) * new_region->array_length);
        current_reg->is_occupied = (int *) malloc (sizeof(int) * new_region->array_length);
        memcpy(current_reg->particle_array, new_region->particle_array, sizeof(particle) * new_region->particles_num);
        memcpy(current_reg->is_occupied, new_region->is_occupied, sizeof(int) * new_region->array_length);
        regions[i].pos_x = i / region_sqt_num;
        regions[i].pos_y = i % region_sqt_num;
    }
    free_region (&new_region);
    return regions;
}

void s_free_regions(region **aim, int num_sqt) {
    int num = num_sqt * num_sqt;
    for (int i = 0; i < num; i++) {
        region *cur = &(*aim)[i];
        free(cur->particle_array);
        free(cur->is_occupied);
    }
    free(*aim);
}

void free_region(region **aim) {
    free((*aim)->particle_array);
    free((*aim)->is_occupied);
    free(*aim);
}