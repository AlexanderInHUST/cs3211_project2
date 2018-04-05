#include "common.h"
#include "util/file_helper.h"
#include "model/particle.h"
#include "model/region.h"
#include "serial/s_image_generate.h"
#include "serial/s_main_loop.h"
#include "serial/s_initial_regions.h"
#include "parallel/p_initial_struct.h"
#include "parallel/p_initial_regions.h"
#include "parallel/p_image_generate.h"
#include "parallel/p_image_store.h"
#include "parallel/p_mpi_environment.h"
#include "parallel/p_main_loop.h"

int main(int argc, char * argv[]) {
    input_data * data = load_file("../input.in");
    region * reg = s_create_regions(data, 5);
    s_start_simulation(reg, data, 5);
    free_input_data(&data);
    s_free_regions(&reg, 5);

//    input_data * data = load_file("../input.in");
//    MPI_Datatype MPI_PARTICLE, MPI_VECTOR_PAIR;
//    MPI_Comm MPI_2D_COMM;
//    int proc_id_x, proc_id_y, proc_num, proc_id;
//    int reg_sqrt_num;
//
//    p_mpi_initial(&MPI_PARTICLE, &MPI_VECTOR_PAIR, &reg_sqrt_num, &proc_num, argc, argv);
//    p_mpi_cart_divide(&proc_id_x, &proc_id_y, &proc_id, reg_sqrt_num, &MPI_2D_COMM);
//    region * reg = p_create_regions(data, proc_id_x, proc_id_y);
//    p_start_simulation(reg, data, proc_id_x, proc_id_y, proc_id, reg_sqrt_num, MPI_2D_COMM, MPI_PARTICLE);

//    ppm_image * image = p_create_ppm_image(reg, proc_id_x, proc_id_y, (int) sqrt(proc_num), MPI_2D_COMM, MPI_PARTICLE);
//    p_store_file(image, "test.ppm", proc_id, proc_id_x, proc_id_y, (int) sqrt(proc_num));


//    p_mpi_finalize();

    return 0;
}