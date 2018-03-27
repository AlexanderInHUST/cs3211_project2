#include "vector_pair.h"

//
// Created by 唐艺峰 on 2018/3/27.
//

void vector_pair_add(vector_pair *a, vector_pair *b) {
    a->to_east = a->to_east + b->to_east;
    a->to_north = a->to_north + b->to_north;
}