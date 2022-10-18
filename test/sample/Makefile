TARGET=sample
include ../shared/Makefile.shared

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -fopenmp -o $(TARGET)

run_$(TARGET):
	../../run-sniper -n4 -c gainestown ./sample


CLEAN_EXTRA=viz          

