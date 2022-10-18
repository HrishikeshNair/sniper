#include <pthread.h>
#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
//#include "sim_api.h"
int main()
{
    //int a[100000];
    //SimRoiStart();
 //int pid = fork();
    #pragma omp parallel for
    for (int i = 0; i < 10; i++) {
	printf("Hello World... from thread = %d\n", omp_get_thread_num());
    }
    //SimRoiEnd();
}

/*
int main()
{
	printf("Hello world\n");
	return 0;
}*/
