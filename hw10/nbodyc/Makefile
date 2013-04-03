CPROGS = nbody nbody_omp 

all: $(CPROGS)

ROOTDIR=${HOME}/ppp
include ${ROOTDIR}/Makefile.inc

OPENMP=-fopenmp 

%.o:%.c
	$(CC) -g $(CFLAGS) $(OPENMP) -c $< -o $@


nbody_omp.o: nbody_omp.c
	$(OMPCC) -g $(OMPCFLAGS) -c $<

nbody: nbody.o $(UTILS)
	$(F77) $(OMPCFLAGS) nbody.o -g $(UTILS) -o $@  $(CLIBS) $(PGPLIBS) -lm
	./nbody > serial.txt

nbody_omp: nbody_omp.o $(UTILS)
	$(F77) $(OMPCFLAGS) nbody_omp.o -g $(UTILS) -o $@  $(CLIBS) $(PGPLIBS) -lm
	./nbody_omp > omp.txt
	diff serial.txt omp.txt
	diff myparticles.txt myparticles_omp.txt

clean:
	rm -f *.o
	rm -f $(CPROGS)
	#rm -f myparticles.txt
