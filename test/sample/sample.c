#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int MAX = 1000; // for an array of size MAX
int THREAD_MAX = 4;
clock_t start, end;
float elapsed_time;


long int *array;

int low=5;

void *change(void *arg) {

    start = clock();	
	
    int id = *(int *)arg;		//threads take an address as input, decide how many bytes to read ex int = 4bytes passing an address to the fn each thread is calling
    printf("thread name = %d\n", id);
        array[low] = 0;
        printf("%d\n",array[5]);
        
        end = clock();
}
//pthread takes in the address without ack ing how big the address is ex int = 4bytes
//typecasting it to how much of the address you want
//int*(arg) -> you want the next 4 bytes from that location (arg is the address)
//*int*(arg) gives the value at that location (4 bytes)
int main() {

    array = malloc(sizeof(long int) * MAX);

    pthread_t threads[THREAD_MAX];
    int arr[THREAD_MAX];	//for passing/printing the thread ids
	
    //start = clock();

    for (int i = 0; i < THREAD_MAX; i++) {// each thread with the particular tsk
        arr[i] = i+1;
        pthread_create(&threads[i], NULL, change, &arr[i]);
    }


    // joining all 4 threads
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(threads[i], NULL);
    
    //end = clock();
    
    clock_t cyc = end-start;
    //elapsed_time = (float)(end - start) / (float)CLOCKS_PER_SEC;
    printf("\n\nCycles: %ld\n", cyc);

}

