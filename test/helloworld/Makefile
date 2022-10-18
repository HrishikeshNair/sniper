CLEAN_EXTRA=viz

#export OMP_NUM_THREADS= 8
TARGET=helloworld
include ../shared/Makefile.shared


$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -fopenmp -o $(TARGET)

run_$(TARGET):
		
	../../run-sniper -v -n 1 -c gainestown --sift -- ./helloworld

#CLEAN_EXTRA=viz


#export OMP_NUM_THREADS=4
#TARGET=helloworld
#include ../shared/Makefile.shared

#OMP_CFLAGS=$(GRAPHITE_CFLAGS) -fopenmp
#OMP_LDFLAGS=$(filter-out -static,$(GRAPHITE_LDFLAGS)) -fopenmp

#$(TARGET): $(TARGET).o
#	$(CC) $(TARGET).o -std=c99 -lm $(SNIPER_LDFLAGS) -fopenmp -o $(TARGET)

#hello: hello.o Makefile
#	$(CC) $(OMP_LDFLAGS) -o hello hello.o -lm 
	

#run_$(TARGET):
	
#	../../run-sniper -n 2 -c gainestown --sift --fast-forward ./helloworld -p 4

