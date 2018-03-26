//
// Created by 唐艺峰 on 2018/3/26.
//

#include "image_painter.h"

void paint_on_ppm(ppm_image *image, particle *part, int x_offset, int y_offset) {
    int start_x = (int) (part->x - part->radius) + x_offset;
    int start_y = (int) (part->y - part->radius) + y_offset;
    int end_x = (int) (part->x + part->radius) + x_offset;
    int end_y = (int) (part->y + part->radius) + y_offset;
    for (int i = MAX(0, start_x); i <= MIN(image->width - 1, end_x); i++) {
        for (int j = MAX(0, start_y); j <= MIN(image->height - 1, end_y); j++) {
            if (image->data[(i * image->width + j) * 3 + 2] == 255
                    || image->data[(i * image->width + j) * 3] == 255) {
                continue;
            }
            if (part->is_small == 1) {
                image->data[(i * image->width + j) * 3] += 1;
                if (image->data[(i * image->width + j) * 3] > 255) {
                    image->data[(i * image->width + j) * 3] = 255;
                }
            } else {
                if ((i - part->x) * (i - part->x) + (j - part->y) * (j - part->y) > part->radius * part->radius) {
                    continue;
                }
                image->data[(i * image->width + j) * 3] = 0;
                image->data[(i * image->width + j) * 3 + 2] = 255;
            }
        }
    }
}

void traverse_image (ppm_image * image) {

}