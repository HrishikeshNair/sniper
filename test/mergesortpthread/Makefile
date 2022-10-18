#export OMP_NUM_THREADS= 8
TARGET=mergesortpthread
include ../shared/Makefile.shared

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -fopenmp -o $(TARGET)

run_$(TARGET):
	../../run-sniper -v -n72 -c gainestown ./mergesortpthread


CLEAN_EXTRA=viz          
