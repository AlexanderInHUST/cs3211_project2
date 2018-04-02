#include "common.h"
#include "util/file_helper.h"
#include "model/particle.h"
#include "model/region.h"
#include "serial/s_image_generate.h"
#include "serial/s_main_loop.h"

int main() {
    input_data * data = load_file("../input.in");
    region * reg = create_regions(data, 5);
    start_simulation(reg, data, 5);
    free_input_data(&data);
    free_regions(&reg, 5);
}