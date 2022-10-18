TARGET=arrayaddition
include ../shared/Makefile.shared

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -fopenmp -o $(TARGET)

run_$(TARGET):
#	../../run-sniper -v -n4 -c --fast-forward gainestown -- ./arrayaddition
	../../run-sniper -n 8 -c gainestown --fast-forward ./arrayaddition


CLEAN_EXTRA=viz          
