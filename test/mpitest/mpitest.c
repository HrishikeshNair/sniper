//#include "/usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/mpicxx.h"
#include <mpi.h>
#include <stdio.h>
//printf("Outside main\n");
int main(int argc, char** argv) {
    printf("Inside main\n");
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    printf("after mpi_init\n");

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    printf("after mpi_comm_world\n");
    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    printf("after mpi_comm_rank\n");
    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    printf("after mpi_get_proc_name\n");
    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);

    // Finalize the MPI environment.
    MPI_Finalize();
    printf("after mpi_finalize\n");
}
