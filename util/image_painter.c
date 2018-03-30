//
// Created by 唐艺峰 on 2018/3/26.
//

#include "image_painter.h"

void paint_on_ppm(ppm_image *image, particle *part, int x_offset, int y_offset) {
    double global_part_x = part->x + x_offset;
    double global_part_y = part->y + y_offset;
    int start_x = (int) (global_part_x - part->radius);
    int start_y = (int) (global_part_y - part->radius);
    int end_x = (int) (global_part_x + part->radius);
    int end_y = (int) (global_part_y + part->radius);
    for (int i = MAX(0, start_x); i <= MIN(image->width - 1, end_x); i++) {
        for (int j = MAX(0, start_y); j <= MIN(image->height - 1, end_y); j++) {
            if (image->data[(i * image->width + j) * 3 + 2] == 255
                    || image->data[(i * image->width + j) * 3] == 255) {
                continue;
            }
            if (part->is_small == 1) {
                image->data[(i * image->width + j) * 3] += RED_P;
                if (image->data[(i * image->width + j) * 3] > 255) {
                    image->data[(i * image->width + j) * 3] = 255;
                }
            } else {
                if (DISTANCE(i, j, global_part_x, global_part_y) > part->radius) {
                    continue;
                }
//                image->data[(i * image->width + j) * 3] = 0;
                image->data[(i * image->width + j) * 3 + 2] = 255;
            }
        }
    }
}

void traverse_image (ppm_image * image) {

}