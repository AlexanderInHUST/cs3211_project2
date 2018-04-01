#include "common.h"
#include "util/file_helper.h"
#include "model/particle.h"
#include "model/region.h"
#include "serial/s_image_generate.h"
#include "serial/s_main_loop.h"

//region * create_region (double grid_size, int num_of_smalls, double small_mass, double small_radius,
//                        int num_of_bigs, char ** bigs_data, int x, int y);

int main() {
    input_data * data = load_file("../input.in");
    region * reg = create_regions(data, 2);
    start_simulation(reg, data, 2);
    free_input_data(&data);
    free_regions(&reg, 2);
//    printf("%ld", sizeof(region));
}