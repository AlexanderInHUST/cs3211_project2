cmake_minimum_required(VERSION 3.8)
project(galaxy_simulation)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/local/Cellar/mpich/3.2_2/include/)

SET(CMAKE_C_COMPILER "/usr/local/Cellar/mpich/3.2_3/bin/mpicc")

set(SOURCE_FILES main.c model/particle.h model/region.c model/region.h model/particle.c common.h util/random.c util/random.h util/input_helper.c util/input_helper.h)

add_executable(galaxy_simulation ${SOURCE_FILES})

