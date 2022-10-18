#include "mpi.h"
//#include "sim_api.h"

#include <stdio.h>
#include <math.h>

int main( int argc, char *argv[] )
{
   printf("Inside main\n");
   int n, myid, numprocs, i;
   double PI25DT = 3.141592653589793238462643;
   double mypi, pi, h, sum, x;

   MPI_Init(&argc,&argv);
   printf("after mpi init\n");
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
   printf("after mpi_comm_size\n");
   MPI_Comm_rank(MPI_COMM_WORLD,&myid);
   printf("after mpi_comm_rank\n");
   n = 100000;

   //SimRoiStart();

   MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
   printf("after mpi_bcast/n");
   h   = 1.0 / (double) n;
   sum = 0.0;
   for (i = myid + 1; i <= n; i += numprocs)
   {
      x = h * ((double)i - 0.5);
      sum += (4.0 / (1.0 + x*x));
   }
   mypi = h * sum;

   printf("local sum for thread %d is %f\n", myid, mypi);
   MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
   printf("after mpi_reduce/n");
   if (myid == 0)
      printf("pi is approximately %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT));

   //SimRoiEnd();

   MPI_Finalize();
   printf("after mpi_finalize\n");
   return 0;
}
