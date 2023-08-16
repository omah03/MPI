#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  int rank, num_procs, token;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  // Receive from the lower process and send to the higher process. Take care
  // of the special case when you are the first process to prevent deadlock.

  if (rank != 0) {
    // TODO: Receive the token from the previous process in the ring
    MPI_Recv(&token, 1, MPI_INT, rank -1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received token %d from process %d\n", rank, token,
           rank - 1);
  } else {
    // TODO: Set the token's value if you are process 0
    token = 100;
  }

  // TODO: send the token to the next process in the ring 
  MPI_Send(&token,1,MPI_INT,(rank +1)%num_procs,0,MPI_COMM_WORLD);
  // Now process 0 can receive from the last process. This makes sure that at
  // least one MPI_Send is initialized before all MPI_Recvs (again, to prevent
  // deadlock)

  if (rank == 0) {
    // TODO: Receive the token from the last process in the ring
    MPI_Recv(&token,1,MPI_INT,rank -1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    printf("Process %d received token %d from process %d\n", rank, token,
           num_procs - 1);
  }

  MPI_Finalize();
}
