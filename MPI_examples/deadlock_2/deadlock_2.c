#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

  char *sendbuf, *recvbuf;
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

  // forcing the program to run with exactly two processes
  if (num_processes != 2) {
    fprintf(stderr, "Must use exactly two processes for this program\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  } else {
    int other = 1 - rank;
    // testing different message sizes that will cause deadlock
    for (int size = 1; size < 2000000000; size *= 10) {
      sendbuf = malloc(size * sizeof(char));
      recvbuf = malloc(size * sizeof(char));
      if (!sendbuf || !recvbuf) {
        fprintf(stderr, "Failed to allocate memory\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
      }
      MPI_Send(sendbuf, size, MPI_CHAR, other, 0, MPI_COMM_WORLD);
      MPI_Recv(recvbuf, size, MPI_CHAR, other, 0, MPI_COMM_WORLD, &status);

      if (rank == 0) {
          printf("Send did not block for %d bytes\n",size);
      }
      free(sendbuf);
      free(recvbuf);
    }
  }

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
