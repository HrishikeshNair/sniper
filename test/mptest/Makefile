TARGET = mptest
include ../shared/Makefile.shared

SNIPER_LDFLAGS := $(filter-out -static,$(GRAPHITE_LDFLAGS)) -fopenmp
SNIPER_CFLAGS += -fopenmp

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -o $(TARGET)

run_$(TARGET):
	OMP_NUM_THREADS=2 OMP_WAIT_POLICY=passive ../../run-sniper -n 3 -c nehalem  --viz -- ./OpenMP 32
