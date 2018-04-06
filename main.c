#include "common.h"
#include "util/file_helper.h"
#include "model/particle.h"
#include "model/region.h"
#include "parallel/p_initial_struct.h"
#include "parallel/p_initial_regions.h"
#include "parallel/p_image_generate.h"
#include "parallel/p_image_store.h"
#include "parallel/p_mpi_environment.h"
#include "parallel/p_main_loop.h"
#include "sequential/s_initial_regions.h"
#include "sequential/s_main_loop.h"
#include "util/timer.h"

int main(int argc, char * argv[]) {
    double start_time = get_wall_time();
    input_data * data = load_file("../input.in");
    region * reg = s_create_regions(data, 2);
    s_start_simulation(reg, data, 2);
    free_input_data(&data);
    s_free_regions(&reg, 2);
    printf("time : %lf\n", get_wall_time() - start_time);

//    double start_time = get_wall_time();
//    input_data * data = load_file("../input.in");
//    MPI_Datatype MPI_SIM_PARTICLE, MPI_PARTICLE, MPI_VECTOR_PAIR;
//    MPI_Comm MPI_2D_COMM;
//    int proc_id_x, proc_id_y, proc_num, proc_id;
//    int reg_sqrt_num;
//
//    p_mpi_initial(&MPI_SIM_PARTICLE, &MPI_PARTICLE, &MPI_VECTOR_PAIR, &reg_sqrt_num, &proc_num, argc, argv);
//    p_mpi_cart_divide(&proc_id_x, &proc_id_y, &proc_id, reg_sqrt_num, &MPI_2D_COMM);
//    region * reg = p_create_regions(data, proc_id_x, proc_id_y);
//    p_start_simulation(reg, data, proc_id_x, proc_id_y, proc_id, reg_sqrt_num, MPI_2D_COMM, MPI_PARTICLE, MPI_SIM_PARTICLE);
//    p_mpi_finalize();
//    printf("time : %lf\n", get_wall_time() - start_time);

    return 0;
}