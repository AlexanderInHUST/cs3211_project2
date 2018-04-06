CC_S		=	gcc
CC_P		=	mpicc
CC_FLAG		=	-O3 -Wall
COM_SRC 	=	model/particle.c model/region.c model/vector_pair.c\
				util/file_helper.c util/image_painter.c util/physics.c util/random.c util/timer.c\
				main.c
SEQ_SRC		=	sequential/s_image_generate.c sequential/s_image_store.c sequential/s_initial_regions.c\
				sequential/s_main_loop.c sequential/s_swap_particles.c
PAR_SRC		=	parallel/p_image_generate.c parallel/p_image_store.c parallel/p_initial_regions.c\
				parallel/p_main_loop.c parallel/p_swap_particles.c parallel/p_initial_struct.c\
				parallel/p_mpi_environment.c

default:
	@echo "Usage: make [clean/seq/par]"

clean:
	rm -rf *.o *.ppm simulation.*

seq:
	$(CC_S) -DSEQ $(CC_FLAG) $(SEQ_SRC) $(COM_SRC) -o simulation.seq

par:
	$(CC_P) $(CC_FLAG) $(PAR_SRC) $(COM_SRC) -o simulation.par