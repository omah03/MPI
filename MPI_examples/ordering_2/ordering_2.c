#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {

  char token;
  MPI_Status status;
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

  // all processes send to rank 0
  if (rank != 0) {
    token = 'A' + rank;
    MPI_Send(&token, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  } else {
    for (int i = 1; i < num_processes; i++) {
      MPI_Recv(&token, 1, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
      printf("Process 0 received token %c from process %d\n", token, status.MPI_SOURCE);
    }
  }

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
