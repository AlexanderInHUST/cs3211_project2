//
// Created by 唐艺峰 on 2018/3/24.
//

#include "random.h"

double next_double (double gird_size) {
    int random;
    static int is_init = 0;
    if (!is_init) {
        time_t t;
        srand((unsigned) time(&t));
        is_init = 1;
    }
    random = rand();
    return ((double)(random)) / ((double)(RAND_MAX)) * gird_size;
}