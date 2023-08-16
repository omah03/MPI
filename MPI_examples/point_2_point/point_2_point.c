#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

  char message[32];
  int err;
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
    if (rank == 0) {
      strncpy(message, "This is not a message!", 32);
      err = MPI_Send(message, 32, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
      if (err == MPI_SUCCESS)
          printf("[%s] Message sent: %s\n", processor_name, message);
    } else {
      err = MPI_Recv(message, 32, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
      if (err == MPI_SUCCESS)
        printf("[%s] Message received: %s\n", processor_name, message);
    }
  }

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
