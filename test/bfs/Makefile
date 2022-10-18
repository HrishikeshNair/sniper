TARGET=bfs
include ../shared/Makefile.shared

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -o $(TARGET)

run_$(TARGET):
#	../../run-sniper -n 4 -c gainestown -c noc ./bfs
#	../../run-sniper -n 4 -c gainestown -c noc --fast-forward ./bfs
#	../../run-sniper -n 2 -c gainestown --fast-forward ./bfs
	../../run-sniper -n 4 -c gainestown ./bfs

CLEAN_EXTRA=viz

