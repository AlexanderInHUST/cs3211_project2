//
// Created by 唐艺峰 on 2018/4/3.
//

#include "s_image_store.h"

void store_file (ppm_image * image, char * file_name) {
    FILE * ppm_file = fopen(file_name, "w");
    if (ppm_file == NULL) {
        fprintf(stderr, "Cannot create file!");
        exit(1);
    }
    fprintf(ppm_file, "P3\n");
    fprintf(ppm_file, "%d %d\n", image->width, image->height);
    fprintf(ppm_file, "255\n");
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            fprintf(ppm_file, " %3d %3d %3d",
                    image->data[(i * image->height + j) * 3 + 0],
                    image->data[(i * image->height + j) * 3 + 1],
                    image->data[(i * image->height + j) * 3 + 2]);
        }
        fprintf(ppm_file, "\n");
    }
    fclose(ppm_file);
}