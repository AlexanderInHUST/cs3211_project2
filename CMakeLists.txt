cmake_minimum_required(VERSION 3.8)
project(galaxy_simulation)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/local/Cellar/mpich/3.2_2/include/)

SET(CMAKE_C_COMPILER "/usr/local/bin/mpicc")

set(SOURCE_FILES main.c model/particle.h model/region.c model/region.h model/particle.c common.h util/random.c util/random.h util/file_helper.c util/file_helper.h sequential/s_main_loop.c sequential/s_main_loop.h model/ppm_image.h sequential/s_image_generate.c sequential/s_image_generate.h model/input_data.h util/image_painter.c util/image_painter.h util/physics.c util/physics.h model/vector_pair.h model/vector_pair.c sequential/s_swap_particles.c sequential/s_swap_particles.h parallel/p_main_loop.c parallel/p_main_loop.h parallel/p_image_generate.c parallel/p_image_generate.h parallel/p_swap_particles.c parallel/p_swap_particles.h sequential/s_initial_regions.c sequential/s_initial_regions.h parallel/p_initial_regions.c parallel/p_initial_regions.h sequential/s_image_store.c sequential/s_image_store.h parallel/p_image_store.c parallel/p_image_store.h parallel/p_initial_struct.c parallel/p_initial_struct.h parallel/p_mpi_environment.c parallel/p_mpi_environment.h util/timer.c util/timer.h)

add_executable(galaxy_simulation ${SOURCE_FILES})

