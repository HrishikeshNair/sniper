#export OMP_NUM_THREADS= 8
TARGET=floydwarshall
include ../shared/Makefile.shared

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -fopenmp -o $(TARGET)

run_$(TARGET):
	../../run-sniper -v -n 4 -c gainestown ./floydwarshall


CLEAN_EXTRA=viz

