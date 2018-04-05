//
// Created by 唐艺峰 on 2018/4/3.
//

#include "p_initial_struct.h"

void p_create_vector_pair(MPI_Datatype *MPI_VECTOR_PAIR) {
    vector_pair tmp;
    MPI_Datatype type[2] = {MPI_DOUBLE, MPI_DOUBLE};
    int block_len[2] = {1, 1};
    MPI_Aint dis[2];
    dis[0] = DIS(tmp.to_east, tmp);
    dis[1] = DIS(tmp.to_north, tmp);
    MPI_Type_create_struct(2, block_len, dis, type, MPI_VECTOR_PAIR);
    MPI_Type_commit(MPI_VECTOR_PAIR);
}

void p_create_particle(MPI_Datatype *MPI_PARTICLE, MPI_Datatype MPI_VECTOR_PAIR) {
    particle tmp;
    MPI_Datatype type[9] = {MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE,
                            MPI_VECTOR_PAIR, MPI_VECTOR_PAIR, MPI_INT};
    int block_len[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    MPI_Aint dis[9];
    dis[0] = DIS(tmp.x, tmp);
    dis[1] = DIS(tmp.y, tmp);
    dis[2] = DIS(tmp.next_x, tmp);
    dis[3] = DIS(tmp.next_y, tmp);
    dis[4] = DIS(tmp.mass, tmp);
    dis[5] = DIS(tmp.radius, tmp);
    dis[6] = DIS(tmp.velocity, tmp);
    dis[7] = DIS(tmp.next_velocity, tmp);
    dis[8] = DIS(tmp.is_small, tmp);
    MPI_Type_create_struct(9, block_len, dis, type, MPI_PARTICLE);
    MPI_Type_commit(MPI_PARTICLE);
}

void p_create_all_structs(MPI_Datatype *MPI_PARTICLE, MPI_Datatype *MPI_VECTOR_PAIR) {
    p_create_vector_pair(MPI_VECTOR_PAIR);
    p_create_particle(MPI_PARTICLE, *MPI_VECTOR_PAIR);
}