#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  MPI_Init(&argc, &argv);

  // Get the number of processes
  int num_processes;
  MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

  // Get the rank of the process
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Request *requests =
      (MPI_Request *) malloc(num_processes * sizeof(MPI_Request));
  MPI_Status *statuses =
      (MPI_Status *) malloc(num_processes * sizeof(MPI_Status));

  char *recv_buffers = (char *)malloc(num_processes * sizeof(char));
  char send_buffers = 'A';

  send_buffers += rank;

  MPI_Isend(&send_buffers, 1, MPI_CHAR, 0, 0,
            MPI_COMM_WORLD, &requests[rank]);

  // all processes send to rank 0
  if (rank == 0) {
    for (int i = 0; i < num_processes; i++)
        MPI_Irecv(&recv_buffers[i], 1, MPI_CHAR, i, 0,
                  MPI_COMM_WORLD, &requests[i]);
    MPI_Waitall(num_processes, requests, statuses);
    for (int i = 0; i < num_processes; i++) {
      printf("Process 0 received token %c from process %d\n", recv_buffers[i],
             statuses[i].MPI_SOURCE);
    }
  }

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
