#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int MAX = 1000;

struct timespec begin, end;



struct values{
  pid_t tid;
  struct timespec st,en;
};

// number of threads
//#define THREAD_MAX 4
int THREAD_MAX = 1;

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
    for(int i = low; i <= high; ++i)
    {
        //output[i] = input1[i] + input2[i];
        output[i] = input1[i];
        for(long int j = 0; j<100; j++)
        {
          output[i] = output[i] + 1;
        }
    }
}

void *call_add(void *arg)		// sending low and high values for each thread to Addition()
{
    //clock_gettime(CLOCK_REALTIME, &begin);
    struct tsk *tsk = arg;
    int low;
    int high;

    pid_t tid = getpid();

    low = tsk->tsk_low;
    high = tsk->tsk_high;

    clock_gettime(CLOCK_REALTIME, &begin);
    Addition(low,high);
    clock_gettime(CLOCK_REALTIME, &end);
    struct values *v = malloc(sizeof(struct values *));
    v -> tid = tid;
    v -> st = begin;
    v -> en = end;
    return ((void*) v);
    //printf("THREAD ID IS: %d\n", tid);
    /*long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Low: %d High: %d\n",low,high);
    printf("Time measured: %.7f seconds.\n\n", elapsed);*/
}

int main() {

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


    //clock_gettime(CLOCK_REALTIME, &begin);

    struct values *v;
    void* temp;

    for (int i = 0; i < THREAD_MAX; i++) {			//giving each tsk to a thread
        tsk = &tsklist[i];					// each thread with the particular tsk
        pthread_create(&threads[i], NULL, call_add, tsk);
    }


    // joining all 4 threads
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(threads[i], &temp);
    v = (temp);
    //clock_gettime(CLOCK_REALTIME, temp);

    printf("c[0] is: %ld\n",output[0]);

    printf("THREAD ID IS: %d\n", v -> tid);

    begin = v->st;
    end = v->en;

    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Time measured: %.9f seconds.\n", elapsed);


    // print output buffer, the output buffer not updated properly,
    // noticed"0" for 1 & 2 thread randomly
    /*
    printf("\n\nFinal array:");
    for (int i = 0; i < MAX; i++)
        printf(" %d", output[i]);
    printf("\n");
    */
}
