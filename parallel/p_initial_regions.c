//
// Created by 唐艺峰 on 2018/4/3.
//

#include "p_initial_regions.h"

region *p_create_regions(input_data *input, int proc_id_x, int proc_id_y) {
    double grid_size = input->grid_size;
    int num_of_smalls = input->num_of_smalls;
    double small_mass = input->mass_of_smalls;
    double small_radius = input->radius_of_smalls;
    int num_of_bigs = input->num_of_bigs;
    char **bigs_data = input->bigs_data;
    region *new_region = (region *) malloc(sizeof(region));

    new_region->pos_x = proc_id_x;
    new_region->pos_y = proc_id_y;
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
    return new_region;
}