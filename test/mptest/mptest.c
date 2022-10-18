#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc, char ** argv)	{
  double **A, *TempIndex, l;
  int i, j, k, N;
  
   N=atoi(argv[1]);
  
  A= (double**) malloc(N*sizeof(double*));
  TempIndex= (double*) malloc(N*N*sizeof(double));
  for (i=0; i<N; i++)
    A[i]=TempIndex+i*N;
	    
  
  /* Initialize Table A with Random Values */
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      A[i][j]=rand()%100;
     for (k = 0; k < N - 1; k++)
	  #pragma omp parallel for private(j, l) 
		  for (i = k+1; i < N; i++) {
			  l = (double) (A[i][k] / A[k][k]);
			  for (j = k+1; j < N; j++)
				  A[i][j] = A[i][j] -l*A[k][j];

 return(0);
}
