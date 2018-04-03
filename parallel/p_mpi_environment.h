//
// Created by 唐艺峰 on 2018/4/3.
//

#ifndef GALAXY_SIMULATION_P_MPI_INITIAL_H
#define GALAXY_SIMULATION_P_MPI_INITIAL_H

#include "../common.h"
#include "p_initial_struct.h"

void p_mpi_initial(MPI_Datatype **MPI_PARTICLE, MPI_Datatype **MPI_VECTOR_PAIR,
                   int *proc_num, int argc, char *argv[]);
void p_mpi_finalize();
void p_mpi_cart_divide(int *proc_id_x, int *proc_id_y, int *proc_id, int reg_sqrt_num, MPI_Comm *MPI_2D_COMM);

#endif //GALAXY_SIMULATION_P_MPI_INITIAL_H
