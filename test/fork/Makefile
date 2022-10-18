TARGET=fork
include ../shared/Makefile.shared

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -o $(TARGET)

run_$(TARGET):
	../../run-sniper -n 4 -c gainestown -sipctrace.py -ssynctrace.py --sift -- ./fork -p 4
