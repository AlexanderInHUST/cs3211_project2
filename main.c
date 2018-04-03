#include <stdio.h>
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

int main(int argc, char * argv[]) {
//    input_data * data = load_file("../input.in");
//    region * reg = s_create_regions(data, 5);
//    s_start_simulation(reg, data, 5);
//    free_input_data(&data);
//    s_free_regions(&reg, 5);

    input_data * data = load_file("../input.in");
    MPI_Datatype *MPI_PARTICLE, *MPI_VECTOR_PAIR;
    MPI_PARTICLE = (MPI_Datatype *) malloc(sizeof(MPI_Datatype));
    MPI_VECTOR_PAIR = (MPI_Datatype *) malloc(sizeof(MPI_Datatype));
    int proc_id, proc_num;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    p_create_all_structs(&MPI_PARTICLE, &MPI_VECTOR_PAIR);
    region * reg = p_create_regions(data, proc_id, (int) sqrt(proc_num));
    ppm_image * image = p_create_ppm_image(reg);
    p_store_file(image, "test.ppm", proc_id, (int) sqrt(proc_num));
    MPI_Finalize();
}