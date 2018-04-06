//
// Created by 唐艺峰 on 2018/4/3.
//

#include "p_initial_struct.h"

void p_create_vector_pair(MPI_Datatype *MPI_VECTOR_PAIR) {
    MPI_Datatype type[2] = {MPI_DOUBLE, MPI_DOUBLE};
    int block_len[2] = {1, 1};
    MPI_Aint dis[2];
    dis[0] = 0;
    dis[1] = sizeof(double) + dis[0];
    MPI_Type_create_struct(2, block_len, dis, type, MPI_VECTOR_PAIR);
    MPI_Type_commit(MPI_VECTOR_PAIR);
}

void p_create_sim_particle(MPI_Datatype *MPI_SIM_PARTICLE) {
    MPI_Datatype type[4] = {MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE};
    int block_len[4] = {1, 1, 1, 1};
    MPI_Aint dis[4];
    dis[0] = 0;
    dis[1] = sizeof(double) + dis[0];
    dis[2] = sizeof(double) + dis[1];
    dis[3] = sizeof(double) + dis[2];
    MPI_Type_create_struct(4, block_len, dis, type, MPI_SIM_PARTICLE);
    MPI_Type_commit(MPI_SIM_PARTICLE);
}

void p_create_particle(MPI_Datatype *MPI_PARTICLE, MPI_Datatype MPI_VECTOR_PAIR) {
    MPI_Datatype type[9] = {MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE,
                            MPI_VECTOR_PAIR, MPI_VECTOR_PAIR, MPI_INT};
    int block_len[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    MPI_Aint dis[9];
    dis[0] = 0;
    dis[1] = sizeof(double) + dis[0];
    dis[2] = sizeof(double) + dis[1];
    dis[3] = sizeof(double) + dis[2];
    dis[4] = sizeof(double) + dis[3];
    dis[5] = sizeof(double) + dis[4];
    dis[6] = sizeof(double) + dis[5];
    dis[7] = sizeof(vector_pair) + dis[6];
    dis[8] = sizeof(vector_pair) + dis[7];
    MPI_Type_create_struct(9, block_len, dis, type, MPI_PARTICLE);
    MPI_Type_commit(MPI_PARTICLE);
}

void p_create_all_structs(MPI_Datatype *MPI_SIM_PARTICLE, MPI_Datatype *MPI_PARTICLE, MPI_Datatype *MPI_VECTOR_PAIR) {
    p_create_vector_pair(MPI_VECTOR_PAIR);
    p_create_sim_particle(MPI_SIM_PARTICLE);
    p_create_particle(MPI_PARTICLE, *MPI_VECTOR_PAIR);
}