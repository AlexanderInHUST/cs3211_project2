//
// Created by 唐艺峰 on 2018/4/3.
//

#ifndef GALAXY_SIMULATION_P_INITIAL_STRUCT_H
#define GALAXY_SIMULATION_P_INITIAL_STRUCT_H

#include "../common.h"
#include "../model/vector_pair.h"
#include "../model/region.h"
#include "../model/ppm_image.h"
#include "../model/particle.h"

#define DIS(aim, base) ((int *)&(aim) - (int *)&(base))

void p_create_vector_pair(MPI_Datatype *MPI_VECTOR_PAIR);
void p_create_particle(MPI_Datatype *MPI_PARTICLE, MPI_Datatype MPI_VECTOR_PAIR);
void p_create_all_structs(MPI_Datatype *MPI_PARTICLE, MPI_Datatype *MPI_VECTOR_PAIR);

#endif //GALAXY_SIMULATION_P_INITIAL_STRUCT_H
