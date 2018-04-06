//
// Created by 唐艺峰 on 2018/4/6.
//


#include "timer.h"

double get_wall_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double) time.tv_sec + (double) time.tv_usec * .000001;
}