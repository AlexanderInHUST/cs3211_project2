#include "common.h"
#include "util/input_helper.h"
#include "model/particle.h"
#include "model/region.h"

//region * create_region (double grid_size, int num_of_smalls, double small_mass, double small_radius,
//                        int num_of_bigs, char ** bigs_data, int x, int y);

int main() {
    input_data * data = load_file("../input.in");
    region * reg = create_region
            (data->grid_size, data->num_of_smalls, data->mass_of_smalls, data->radius_of_smalls, data->num_of_bigs,
            data->bigs_data, 0, 0);
    traverse_region(reg);
    free_input_data(&data);
    free_region(&reg);
}