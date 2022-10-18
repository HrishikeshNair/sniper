#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int n, totaln, **C, **D;                    /* Variable declarations */
pthread_t *threads;
pthread_mutex_t mutexprint;
long thread, threadcount;

void *LowestTerm(void* rank);

int main(int argc, char *argv[]) {

    int i, j, k;                        /* Variable declarations */
    char filename[50];

    threadcount = atoi(argv[1]);
    threads = malloc (threadcount * sizeof(pthread_t));

    printf("Enter filename: ");             /* User enters filename for directed graph values */
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {                   /* Check whether file exists or not */
        printf("File does not exist");
        return 1;
    }

    fscanf(fp, "%d", &n);                   /* Obtain size of matrix */

    totaln = n * n;

    C = (int **)malloc(n * sizeof(int *));          /* Allocate memory for matrix arrays */
    D = (int **)malloc(n * sizeof(int *));

    for (i = 0; i < n; i++) {               /* Allocate matrices into 2D arrays */
        C[i] = (int *)malloc(n * sizeof(int));
        D[i] = (int *)malloc(n * sizeof(int));
    }


    for (i = 0; i < n; i++) {               /* Read matrix from file into C array */
        for (j = 0; j < n; j++) {
            fscanf(fp, "%d", &C[i][j]);
        }
    }

    printf("Cost Adjacency Matrix:\n");         /* Print cost adjacency matrix */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf(" \n");
    }

    for (i = 0; i < n; i++) {               /* Copy matrix from C array into D array */
        for (j = 0; j < n; j++) {
            D[i][j] = C[i][j];
        }
    }

    printf("Distance matrix:\n");



    for (thread = 0; thread < threadcount; thread++) {
        pthread_create(&threads[thread], NULL, LowestTerm, (void*) thread);
    }
    for (thread = 0; thread < threadcount; thread++) {
        pthread_join(threads[thread], NULL);
    }

    pthread_mutex_destroy (&mutexprint);
    free(threads);
    pthread_exit(NULL);

}


void *LowestTerm(void* rank) {

    int i, j, k;                        /* Variable declarations */
    long mythread = (long) rank;

    int istart = ((int)mythread * n) / (int)threadcount;    /* Create matrix row start and finish parameters for each thread */
    int ifinish = ((((int)mythread + 1) * n) / (int)threadcount);

    for (k = 0; k < n; k++) {               /* Find shortest path for each value in each row for each of designated thread's rows */
        for (i = istart; i < ifinish; i++) {
            for (j = 0; j < n; j++) {
                if (D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }

    pthread_mutex_lock (&mutexprint);           /* Print distance matrix */
    for (i = istart; i < ifinish; i++) {
        printf("Thread %ld: ", mythread);		// d to ld
        for (j = 0; j < n; j++) {
            printf("%d ", D[i][j]);
        }
        printf(" \n");
    }
    pthread_mutex_unlock (&mutexprint);


    return NULL;
}
