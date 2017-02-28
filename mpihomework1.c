#include <stdio.h>
#include <mpi.h>

int main(int argc, char ** argv) {
  MPI_Init(NULL, NULL);
  /* Find out rank*/
  int root = 0;
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int number, number4;
  /* input, root*/
  if (world_rank == root) {
    printf( "\nEnter a value: ");
    if (scanf("%d", &number) == 1)
      {
        printf("You entered %d\n", number);
      }
    else {
      printf("Failed to read\n");
    }

    }
  /* calculation, slave*/
  MPI_Bcast(&number, 1, MPI_INT, root, MPI_COMM_WORLD);
  number4 = number * world_rank;
  printf("Process rank %d received number %d from process 0, and multiply its rank to get %d\n",
         world_rank, number, number4);


  MPI_Finalize();
  return 0;
  }
