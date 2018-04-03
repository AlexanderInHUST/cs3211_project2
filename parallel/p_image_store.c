//
// Created by 唐艺峰 on 2018/4/3.
//

#include "p_image_store.h"

void p_store_file (ppm_image * image, char * file_name, int proc_id, int proc_id_x, int proc_id_y, int region_sqt_num) {
    MPI_File file_handle;
    MPI_File_open(MPI_COMM_WORLD, file_name, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &file_handle);
    char first_line[10] = "P3\n";
    char second_line[20];
    char third_line[10] = "255\n";
    sprintf(second_line, "%d %d\n", image->width * region_sqt_num, image->height * region_sqt_num);
    int dis_1, dis_2, dis_3;
    dis_1 = sizeof(char) * strlen(first_line);
    dis_2 = sizeof(char) * strlen(second_line) + dis_1;
    dis_3 = sizeof(char) * strlen(third_line) + dis_2;
    if (proc_id == 0) {
        MPI_File_write_at(file_handle, 0, first_line, (int)strlen(first_line), MPI_CHAR, MPI_STATUS_IGNORE);
        MPI_File_write_at(file_handle, dis_1, second_line, (int)strlen(second_line), MPI_CHAR, MPI_STATUS_IGNORE);
        MPI_File_write_at(file_handle, dis_2, third_line, (int)strlen(third_line), MPI_CHAR, MPI_STATUS_IGNORE);
    }

    int start_dis = (proc_id_x * image->height * (region_sqt_num * (image->width * 3 * 4) + 1))
                    + (proc_id_y * (image->width * 3 * 4)) + dis_3;
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            char part_data[20];
            sprintf(part_data, " %3d %3d %3d",
                    image->data[(i * image->height + j) * 3 + 0],
                    image->data[(i * image->height + j) * 3 + 1],
                    image->data[(i * image->height + j) * 3 + 2]);
            MPI_File_write_at(file_handle, start_dis + j * 12, part_data, 12, MPI_CHAR, MPI_STATUS_IGNORE);
        }
        if (proc_id_y == region_sqt_num - 1) {
            MPI_File_write_at(file_handle, start_dis + image->width * 12, "\n", 1, MPI_CHAR, MPI_STATUS_IGNORE);
        }
        start_dis += (region_sqt_num * (image->width * 3 * 4) + 1);
    }
    MPI_File_close(&file_handle);
}