TARGET=matrixmult
include ../../shared/Makefile.shared

#$(SNIPER_CFLAGS) += -fopenmp

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -fopenmp -o $(TARGET)

run_$(TARGET):
	../../run-sniper -v -n 4 -c gainestown --roi --fast-forward ./matrixmult

CLEAN_EXTRA=viz
