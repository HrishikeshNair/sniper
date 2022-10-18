#export OMP_NUM_THREADS= 8
TARGET=saxpyocl
include ../shared/Makefile.shared


$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -o $(TARGET)

run_$(TARGET):
		
	../../run-sniper -v -n 8 -c gainestown --sift -- ./saxpyocl

CLEAN_EXTRA=viz
