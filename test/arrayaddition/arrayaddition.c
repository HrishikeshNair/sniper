#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int MAX = 10000;

struct timespec beginw, endw, beginadd, endadd, begincadd, endcadd; 

// number of threads
//#define THREAD_MAX 4
int THREAD_MAX = 64;

//using namespace std;
// array of size MAX
long int *input1;
//long int *input2;
long int *output;


struct tsk {
    int tsk_no;
    int tsk_low;
    int tsk_high;
};

void Addition(int low,int high) {
    clock_gettime(CLOCK_REALTIME, &beginadd); 
    for(int i = low; i <= high; ++i)
            //output[i] = input1[i] + input2[i];
            {
            	output[i] = input1[i];
              for(long int j = 0; j<1000; j++)
           	 {
            		output[i] = output[i] + 1;
            	}
            }
    clock_gettime(CLOCK_REALTIME, &endadd);
    long seconds = endadd.tv_sec - beginadd.tv_sec;
    long nanoseconds = endadd.tv_nsec - beginadd.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Low: %d High: %d\n",low,high);
    printf("Time measured for Addition: %.9f seconds.\n\n", elapsed);
}

void *call_add(void *arg)		// sending low and high values for each thread to Addition()
{
    clock_gettime(CLOCK_REALTIME, &begincadd); 
    struct tsk *tsk = arg;
    int low;
    int high;

    pid_t tid = gettid();

    low = tsk->tsk_low;
    high = tsk->tsk_high;

    Addition(low,high);
    clock_gettime(CLOCK_REALTIME, &endcadd);
    return((void*) tid);
    //printf("THREAD ID IS: %d\n", tid);
    /* long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Low: %d High: %d\n",low,high);
    printf("Time measured: %.7f seconds.\n\n", elapsed); */



}

int main() {

    //pthread_t thread_id[4];
    void* status;

    input1 = malloc(sizeof(long int) * MAX);
    //input2 = malloc(sizeof(long int) * MAX);
    output =  malloc(sizeof(long int) * MAX);

    for (int i = 0; i < MAX; i++) {
            input1[i] = rand() % 1000;
            //input2[i] = rand() % 1000;
    }
    
    //printf("\n a[0] is: %ld\n",input1[0]);

    /*
    printf("\n\nInput array 1:");
    for (int i = 0; i < MAX; i++)
        printf(" %d", input1[i]);
    printf("\n");

    printf("\n\nInput array 2:");
    for (int i = 0; i < MAX; i++)
        printf(" %d", input2[i]);
    printf("\n");
    */

    pthread_t threads[THREAD_MAX];		// creating an array of threads
    struct tsk tsklist[THREAD_MAX];		// array of structure tsk, each tsk with high low and tskno
    struct tsk *tsk;

    int len = MAX / THREAD_MAX;

    int low = 0;

    for(int i = 0; i < THREAD_MAX; i++, low += len) {		//giving low and high to each tsk
        tsk = &tsklist[i];
        tsk->tsk_no = i;

        tsk->tsk_low = low;
        tsk->tsk_high = low + len - 1;
        if (i == (THREAD_MAX - 1))
            tsk->tsk_high = MAX - 1;
      }


    clock_gettime(CLOCK_REALTIME, &beginw);
    
    
    void* tid;
    
    for (int i = 0; i < THREAD_MAX; i++) {			//giving each tsk to a thread 
        tsk = &tsklist[i];					// each thread with the particular tsk
        pthread_create(&threads[i], NULL, call_add, tsk);
    }

    // joining all 4 threads
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(threads[i], &tid);
        
    clock_gettime(CLOCK_REALTIME, &endw);
    
     printf("c[0] is: %ld\n",output[0]);
    
    long seconds = endw.tv_sec - beginw.tv_sec;
    long nanoseconds = endw.tv_nsec - beginw.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;	
    printf("Time measured for all threads: %.9f seconds.\n", elapsed); 
    
    printf("THREAD ID IS: %d\n", (int) tid);

    // print output buffer, the output buffer not updated properly,
    // noticed"0" for 1 & 2 thread randomly
    /*
    printf("\n\nFinal array:");
    for (int i = 0; i < MAX; i++)
        printf(" %d", output[i]);
    printf("\n");
    */
}

