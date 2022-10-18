#export OMP_NUM_THREADS= 8
TARGET=matrixmult
include ../shared/Makefile.shared

#$(SNIPER_CFLAGS) += -fopenmp

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -fopenmp -o $(TARGET)

run_$(TARGET):
		
	../../run-sniper -v -n 64 -c kingscross -c noc -c riscv --sift -- ./matrixmult	


CLEAN_EXTRA=viz
