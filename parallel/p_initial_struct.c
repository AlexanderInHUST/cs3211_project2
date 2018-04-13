//
// Created by 唐艺峰 on 2018/4/3.
//

#include "p_initial_struct.h"

void p_create_vector_pair(MPI_Datatype *MPI_VECTOR_PAIR) {
    MPI_Datatype type[2] = {MPI_DOUBLE, MPI_DOUBLE};
    int block_len[2] = {1, 1};
    MPI_Aint dis[2];
    MPI_Aint double_extent, double_bd;
    MPI_Type_get_extent(MPI_DOUBLE, &double_bd, &double_extent);
    dis[0] = 0;
    dis[1] = double_extent + dis[0];
    MPI_Type_create_struct(2, block_len, dis, type, MPI_VECTOR_PAIR);
    MPI_Type_commit(MPI_VECTOR_PAIR);
}

void p_create_sim_particle(MPI_Datatype *MPI_SIM_PARTICLE) {
    MPI_Datatype type[4] = {MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE};
    int block_len[4] = {1, 1, 1, 1};
    MPI_Aint dis[4];
    MPI_Aint double_extent, double_bd;
    MPI_Type_get_extent(MPI_DOUBLE, &double_bd, &double_extent);
    dis[0] = 0;
    dis[1] = double_extent + dis[0];
    dis[2] = double_extent + dis[1];
    dis[3] = double_extent + dis[2];
    MPI_Type_create_struct(4, block_len, dis, type, MPI_SIM_PARTICLE);
    MPI_Type_commit(MPI_SIM_PARTICLE);
}

void p_create_particle(MPI_Datatype *MPI_PARTICLE, MPI_Datatype MPI_VECTOR_PAIR) {
    MPI_Datatype type[9] = {MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE,
                            MPI_VECTOR_PAIR, MPI_VECTOR_PAIR, MPI_INT};
    int block_len[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    MPI_Aint dis[9];
    MPI_Aint double_extent, vector_extent;
    MPI_Aint double_bd, vector_bd;
    MPI_Type_get_extent(MPI_DOUBLE, &double_bd, &double_extent);
    MPI_Type_get_extent(MPI_VECTOR_PAIR, &vector_bd, &vector_extent);
    dis[0] = 0;
    dis[1] = double_extent + dis[0];
    dis[2] = double_extent + dis[1];
    dis[3] = double_extent + dis[2];
    dis[4] = double_extent + dis[3];
    dis[5] = double_extent + dis[4];
    dis[6] = double_extent + dis[5];
    dis[7] = vector_extent + dis[6];
    dis[8] = vector_extent + dis[7];
    MPI_Type_create_struct(9, block_len, dis, type, MPI_PARTICLE);
    MPI_Type_commit(MPI_PARTICLE);
}

void p_create_all_structs(MPI_Datatype *MPI_SIM_PARTICLE, MPI_Datatype *MPI_PARTICLE, MPI_Datatype *MPI_VECTOR_PAIR) {
    p_create_vector_pair(MPI_VECTOR_PAIR);
    p_create_sim_particle(MPI_SIM_PARTICLE);
    p_create_particle(MPI_PARTICLE, *MPI_VECTOR_PAIR);
}