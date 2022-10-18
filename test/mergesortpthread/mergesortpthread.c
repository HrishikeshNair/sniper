#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>


int opt_a;
int opt_t;
int opt_r;


//clock_t start, end;	//
//double cpu_time_used;	//

    struct timespec begin, end; 






// number of elements in array
//#define MAX 15
//#define MAX 16
int MAX;

// number of threads
//#define THREAD_MAX 4
int THREAD_MAX;

//using namespace std;

// array of size MAX
int *a;

// thread control parameters
struct tsk {
    int tsk_no;
    int tsk_low;
    int tsk_high;
};

// merge function for merging two parts
void
merge(int low, int mid, int high)
{

    // n1 is size of left part and n2 is size of right part
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *left = malloc(n1 * sizeof(int));
    int *right = malloc(n2 * sizeof(int));

    int i;
    int j;

    // storing values in left part
    for (i = 0; i < n1; i++)
        left[i] = a[i + low];

    // storing values in right part
    for (i = 0; i < n2; i++)
        right[i] = a[i + mid + 1];

    int k = low;

    i = j = 0;

    // merge left and right in ascending order
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }

    // insert remaining values from left
    while (i < n1)
        a[k++] = left[i++];

    // insert remaining values from right
    while (j < n2)
        a[k++] = right[j++];

    free(left);
    free(right);
}

// merge sort function
void
merge_sort(int low, int high)
{

    // calculating mid point of array
    int mid = low + (high - low) / 2;

    if (low < high) {
        // calling first half
        merge_sort(low, mid);

        // calling second half
        merge_sort(mid + 1, high);

        // merging the two halves
        merge(low, mid, high);
    }
}

// thread function for multi-threading
void *
merge_sort123(void *arg)
{
    struct tsk *tsk = arg;
    int low;
    int high;

    // calculating low and high
    low = tsk->tsk_low;
    high = tsk->tsk_high;

    // evaluating mid point
    int mid = low + (high - low) / 2;

    if (low < high) {
        merge_sort(low, high);
        //merge_sort(mid + 1, high);
        //merge(low, mid, high);
    }

    return 0;
}


void merge_serial(struct tsk tsklist[], int low, int high)
{ 
	int mid = (low + high) / 2; 
	if(low < high)
	{ 
		merge_serial(tsklist,low,mid); 
		merge_serial(tsklist,mid+1,high); 
		struct tsk *tskl = &tsklist[low]; 
		struct tsk *tskm = &tsklist[mid]; 
		struct tsk *tskh = &tsklist[high]; 
		merge(tskl->tsk_low, tskm->tsk_high, tskh->tsk_high); 
	} 
}


// Driver Code
int
main(int argc, char **argv)
{


    //start = clock();	//
   //clock_gettime(CLOCK_REALTIME, &begin); //    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin) for cpu time


    char *cp;
    struct tsk *tsk;

    --argc;
    ++argv;

    MAX = 4096;    //131072
    THREAD_MAX = 72;

    // use new/general algorithm by default
    opt_a = 1;
  

    for (; argc > 0; --argc, ++argv) {
        cp = *argv;
        if (*cp != '-')
            break;

        switch (cp[1]) {
        case 'M':  // array count
            MAX = atoi(cp + 2);
            break;

        case 'T':  // thread count
            THREAD_MAX = atoi(cp + 2);
            break;

        case 'a':  // change algorithm
            opt_a = !opt_a;
            break;

        case 'r':  // do _not_ use rand -- use linear increment
            opt_r = !opt_r;
            break;

        case 't':  // tracing
            opt_t = !opt_t;
            break;

        default:
            break;
        }
    }

    // allocate the array
    a = malloc(sizeof(int) * MAX);

    // generating random values in array
    if (opt_t)
        printf("ORIG:");
    for (int i = 0; i < MAX; i++) {
        if (opt_r)
            a[i] = MAX - i;
        else
            a[i] = rand() % 100;
        if (opt_t)
            printf(" %d", a[i]);
    }
               // printf("\n\nUnsorted array:");	//
    		//for (int i = 0; i < MAX; i++)		//
        	//	printf(" %d", a[i]);		//
    		//printf("\n");				//
    if (opt_t)
        printf("\n");

    pthread_t threads[THREAD_MAX];
    struct tsk tsklist[THREAD_MAX];

    int len = MAX / THREAD_MAX;

    if (opt_t)
        printf("THREADS:%d MAX:%d LEN:%d\n", THREAD_MAX, MAX, len);

    int low = 0;

    for (int i = 0; i < THREAD_MAX; i++, low += len) {
        tsk = &tsklist[i];
        tsk->tsk_no = i;

        if (opt_a) {
            tsk->tsk_low = low;
            tsk->tsk_high = low + len - 1;
            if (i == (THREAD_MAX - 1))
                tsk->tsk_high = MAX - 1;
        }

        else {
            tsk->tsk_low = i * (MAX / THREAD_MAX);
            tsk->tsk_high = (i + 1) * (MAX / THREAD_MAX) - 1;
        }

        if (opt_t)
            printf("RANGE %d: %d %d\n", i, tsk->tsk_low, tsk->tsk_high);
    }
	clock_gettime(CLOCK_REALTIME, &begin);
    // creating 4 threads
    for (int i = 0; i < THREAD_MAX; i++) {
        tsk = &tsklist[i];
        pthread_create(&threads[i], NULL, merge_sort123, tsk);
    }

    // joining all 4 threads
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(threads[i], NULL);
	
	
	clock_gettime(CLOCK_REALTIME, &end);
	
    // show the array values for each thread
    if (opt_t) {
        for (int i = 0; i < THREAD_MAX; i++) {
            tsk = &tsklist[i];
            printf("SUB %d:", tsk->tsk_no);
            for (int j = tsk->tsk_low; j <= tsk->tsk_high; ++j)
                printf(" %d", a[j]);
            printf("\n");
        }
    }
    
    
	//clock_gettime(CLOCK_REALTIME, &begin);
	
	
    // merging the final 4 parts
    if (opt_a) 
    	{
     		merge_serial(tsklist,0,THREAD_MAX-1);
     
    	}
  	
    else {
        merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1);
        merge(MAX / 2, MAX / 2 + (MAX - 1 - MAX / 2) / 2, MAX - 1);
        merge(0, (MAX - 1) / 2, MAX - 1);
    }
	//clock_gettime(CLOCK_REALTIME, &end);
	
	
    // displaying sorted array
   // printf("\n\nSorted array:");
    //for (int i = 0; i < MAX; i++)
     //   printf(" %d", a[i]);
    //printf("\n");
	
	
    //clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Time measured: %.9f seconds.\n", elapsed);
    
    //end = clock();								//
    //cpu_time_used = ((double) (end - start))*1000000000000 / CLOCKS_PER_SEC;	//
    //printf("Time taken: %f 10^(-12)s\n", cpu_time_used);			//
		
	
    return 0;
}






























/*// CPP Program to implement merge sort using
// multi-threading
#include <iostream>
#include <pthread.h>
#include <time.h>

// number of elements in array
#define MAX 20

// number of threads
#define THREAD_MAX 4

using namespace std;

// array of size MAX
int a[MAX];
int part = 0;

// merge function for merging two parts
void merge(int low, int mid, int high)
{
	int* left = new int[mid - low + 1];
	int* right = new int[high - mid];

	// n1 is size of left part and n2 is size
	// of right part
	int n1 = mid - low + 1, n2 = high - mid, i, j;

	// storing values in left part
	for (i = 0; i < n1; i++)
		left[i] = a[i + low];

	// storing values in right part
	for (i = 0; i < n2; i++)
		right[i] = a[i + mid + 1];

	int k = low;
	i = j = 0;

	// merge left and right in ascending order
	while (i < n1 && j < n2) {
		if (left[i] <= right[j])
			a[k++] = left[i++];
		else
			a[k++] = right[j++];
	}

	// insert remaining values from left
	while (i < n1) {
		a[k++] = left[i++];
	}

	// insert remaining values from right
	while (j < n2) {
		a[k++] = right[j++];
	}
}

// merge sort function
void merge_sort(int low, int high)
{
	// calculating mid point of array
	int mid = low + (high - low) / 2;
	if (low < high) {

		// calling first half
		merge_sort(low, mid);

		// calling second half
		merge_sort(mid + 1, high);

		// merging the two halves
		merge(low, mid, high);
	}
}

// thread function for multi-threading
void* merge_sort(void* arg)
{
	// which part out of 4 parts
	int thread_part = part++;

	// calculating low and high
	int low = thread_part * (MAX / 4);
	int high = (thread_part + 1) * (MAX / 4) - 1;

	// evaluating mid point
	int mid = low + (high - low) / 2;
	if (low < high) {
		merge_sort(low, mid);
		merge_sort(mid + 1, high);
		merge(low, mid, high);
	}
}

// Driver Code
int main()
{
	// generating random values in array
	for (int i = 0; i < MAX; i++)
		a[i] = rand() % 100;

	// t1 and t2 for calculating time for
	// merge sort
	clock_t t1, t2;

	t1 = clock();
	pthread_t threads[THREAD_MAX];

	// creating 4 threads
	for (int i = 0; i < THREAD_MAX; i++)
		pthread_create(&threads[i], NULL, merge_sort,
										(void*)NULL);

	// joining all 4 threads
	for (int i = 0; i < 4; i++)
		pthread_join(threads[i], NULL);

	// merging the final 4 parts
	merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1);
	merge(MAX / 2, MAX/2 + (MAX-1-MAX/2)/2, MAX - 1);
	merge(0, (MAX - 1)/2, MAX - 1);

	t2 = clock();

	// displaying sorted array
	cout << "Sorted array: ";
	for (int i = 0; i < MAX; i++)
		cout << a[i] << " ";

	// time taken by merge sort in seconds
	cout << "Time taken: " << (t2 - t1) /
			(double)CLOCKS_PER_SEC << endl;

	return 0;
}*/
