//
// Created by 唐艺峰 on 2018/4/3.
//

#include "p_initial_struct.h"

void p_create_vector_pair(MPI_Datatype **MPI_VECTOR_PAIR) {
    vector_pair tmp;
    MPI_Datatype type[2] = {MPI_DOUBLE, MPI_DOUBLE};
    int block_len[2] = {sizeof(double), sizeof(double)};
    MPI_Aint dis[2];
    dis[0] = (int *)&tmp.to_east - (int *)&tmp;
    dis[1] = (int *)&tmp.to_north - (int *)&tmp;
    MPI_Type_create_struct(2, block_len, dis, type, *MPI_VECTOR_PAIR);
    MPI_Type_commit(*MPI_VECTOR_PAIR);
}

void p_create_particle(MPI_Datatype **MPI_PARTICLE, MPI_Datatype MPI_VECTOR_PAIR) {
    particle tmp;
    MPI_Datatype type[9] = {MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE,
                            MPI_VECTOR_PAIR, MPI_VECTOR_PAIR, MPI_INT};
    int block_len[9] = {sizeof(double), sizeof(double), sizeof(double), sizeof(double), sizeof(double), sizeof(double),
                        sizeof(vector_pair), sizeof(vector_pair), sizeof(int)};
    MPI_Aint dis[9];
    dis[0] = (int *)&tmp.x - (int *)&tmp;
    dis[1] = (int *)&tmp.y - (int *)&tmp;
    dis[2] = (int *)&tmp.next_x - (int *)&tmp;
    dis[3] = (int *)&tmp.next_y - (int *)&tmp;
    dis[4] = (int *)&tmp.mass - (int *)&tmp;
    dis[5] = (int *)&tmp.radius - (int *)&tmp;
    dis[6] = (int *)&tmp.velocity - (int *)&tmp;
    dis[7] = (int *)&tmp.next_velocity - (int *)&tmp;
    dis[8] = (int *)&tmp.is_small - (int *)&tmp;
    MPI_Type_create_struct(9, block_len, dis, type, *MPI_PARTICLE);
    MPI_Type_commit(*MPI_PARTICLE);
}

void p_create_all_structs(MPI_Datatype **MPI_PARTICLE, MPI_Datatype **MPI_VECTOR_PAIR) {
    p_create_vector_pair(MPI_VECTOR_PAIR);
    p_create_particle(MPI_PARTICLE, **MPI_VECTOR_PAIR);
}