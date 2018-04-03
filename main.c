#include <stdio.h>
#include "common.h"
#include "util/file_helper.h"
#include "model/particle.h"
#include "model/region.h"
#include "serial/s_image_generate.h"
#include "serial/s_main_loop.h"
#include "serial/s_initial_regions.h"

int main(int argc, char * argv[]) {
    input_data * data = load_file("../input.in");
    region * reg = s_create_regions(data, 5);
    s_start_simulation(reg, data, 5);
    free_input_data(&data);
    s_free_regions(&reg, 5);
//    MPI_Init(&argc, &argv);
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    printf("hello %d\n", rank);
//    MPI_Finalize();
}