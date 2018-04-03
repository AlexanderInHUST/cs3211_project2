cmake_minimum_required(VERSION 3.8)
project(galaxy_simulation)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/local/Cellar/mpich/3.2_2/include/)

SET(CMAKE_C_COMPILER "/usr/local/Cellar/mpich/3.2_3/bin/mpicc")

set(SOURCE_FILES main.c model/particle.h model/region.c model/region.h model/particle.c common.h util/random.c util/random.h util/file_helper.c util/file_helper.h serial/s_main_loop.c serial/s_main_loop.h model/ppm_image.h serial/s_image_generate.c serial/s_image_generate.h model/input_data.h util/image_painter.c util/image_painter.h util/physics.c util/physics.h model/vector_pair.h model/vector_pair.c serial/s_swap_particles.c serial/s_swap_particles.h parallel/p_main_loop.c parallel/p_main_loop.h parallel/p_image_generate.c parallel/p_image_generate.h parallel/p_swap_particles.c parallel/p_swap_particles.h serial/s_initial_regions.c serial/s_initial_regions.h parallel/p_initial_regions.c parallel/p_initial_regions.h serial/s_image_store.c serial/s_image_store.h parallel/p_image_store.c parallel/p_image_store.h parallel/p_initial_struct.c parallel/p_initial_struct.h)

add_executable(galaxy_simulation ${SOURCE_FILES})

