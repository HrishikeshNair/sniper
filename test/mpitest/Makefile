MPICC=mpicc
MPILD=mpicc
MPIRUN=mpirun


EXECS=mpitest
MPICC?=mpicc

all: ${EXECS}

mpitest: mpitest.c
	${MPICC} -o mpitest mpitest.c
	../../run-sniper --mpi -n 4 -c gainestown -- ./a.out

clean:
	rm ${EXECS}

run_mpirun:
	../../run-sniper --mpi --mpi-ranks=2 --mpi-exec="mpirun -genv ENVNAME VALUE" -n 4 -c gainestown -- ./mpitest	
