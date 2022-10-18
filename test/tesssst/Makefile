export OMP_NUM_THREADS=10000
TARGET=tesssst
include ../shared/Makefile.shared

$(SNIPER_CFLAGS) += -fopenmp

$(TARGET): $(TARGET).o
        $(CC) $(TARGET).o -std=c99 -lm $(SNIPER_LDFLAGS) -fopenmp -o $(TARGET)

run_$(TARGET):
        ../../run-sniper -n 4 -c gainestown --roi --fast-forward ./abc

CLEAN_EXTRA=viz

