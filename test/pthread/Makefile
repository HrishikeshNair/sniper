TARGET=pthread
include ../shared/Makefile.shared

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -o $(TARGET)

run_$(TARGET):
	../../run-sniper -v -n 4 -c gainestown --sift -- ./pthread -p 32


CLEAN_EXTRA=viz
