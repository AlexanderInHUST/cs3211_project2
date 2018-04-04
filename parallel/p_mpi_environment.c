//
// Created by 唐艺峰 on 2018/4/3.
//

#include "p_mpi_environment.h"

void p_mpi_initial(MPI_Datatype *MPI_PARTICLE, MPI_Datatype *MPI_VECTOR_PAIR,
                   int *proc_num, int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, proc_num);
    p_create_all_structs(MPI_PARTICLE, MPI_VECTOR_PAIR);
}

void p_mpi_finalize() {
    MPI_Finalize();
}

void p_mpi_cart_divide(int *proc_id_x, int *proc_id_y, int *proc_id, int reg_sqrt_num, MPI_Comm *MPI_2D_COMM) {
    int dims[2] = {reg_sqrt_num, reg_sqrt_num};
    int periods[2] = {0, 0};
    int ranks[2];
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 1, MPI_2D_COMM);
    MPI_Comm_rank(*MPI_2D_COMM, proc_id);
    MPI_Cart_coords(*MPI_2D_COMM, *proc_id, 2, ranks);
    *proc_id_x = ranks[0];
    *proc_id_y = ranks[1];
}