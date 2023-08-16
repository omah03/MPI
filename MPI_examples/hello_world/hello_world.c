#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
  // Initialize the MPI environment.
  MPI_Init(&argc, &argv);

  // Get the number of processes
  int num_processes;
  MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

  // Get the rank of the process
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  // Print off a hello world message
  printf("Hello world, processor: %s, rank: %d, total num of processors: %d\n",
         processor_name, rank, num_processes);

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
