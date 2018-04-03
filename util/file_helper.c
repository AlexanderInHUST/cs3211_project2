//
// Created by 唐艺峰 on 2018/3/24.
//

#include "file_helper.h"

input_data * load_file (char * file_name) {
    FILE * input_file = fopen(file_name, "r");
    if (input_file == NULL) {
        fprintf(stderr, "File not found!");
        exit(1);
    }
    input_data * data = (input_data *) malloc(sizeof(input_data));
    fscanf(input_file, "TimeSlots: %d\n", &data->time_slots);
    fscanf(input_file, "TimeStep: %lf\n", &data->time_step);
    fscanf(input_file, "Horizon: %d\n", &data->horizon);
    fscanf(input_file, "GridSize: %d\n", &data->grid_size);
    fscanf(input_file, "NumberOfSmallParticles: %d\n", &data->num_of_smalls);
    fscanf(input_file, "SmallParticleMass: %lf\n", &data->mass_of_smalls);
    fscanf(input_file, "SmallParticleRadius: %lf\n", &data->radius_of_smalls);
    fscanf(input_file, "NumberOfLargeParticles: %d\n", &data->num_of_bigs);
    data->bigs_data = (char **) malloc(sizeof(char *) * data->num_of_bigs);
    for (int i = 0; i < data->num_of_bigs; i++) {
        char temp_str[MAX_LINE_LEN];
        fgets(temp_str, MAX_LINE_LEN, input_file);
        data->bigs_data[i] = (char *) malloc(sizeof(char) * (strlen(temp_str) + 1));
        memset(data->bigs_data[i], '\0', strlen(temp_str) + 1);
        strcpy(data->bigs_data[i], temp_str);
    }
    fclose(input_file);
    return data;
}

void free_input_data (input_data ** data) {
    for (int i = 0; i < (*data)->num_of_bigs; i++) {
        free ((*data)->bigs_data[i]);
    }
    free ((*data)->bigs_data);
    free (*data);
}

void free_output_data (ppm_image ** image) {
    free((*image)->data);
    free((*image));
}