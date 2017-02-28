#include <stdio.h>
#include <mpi.h>

int main(int argc, char ** argv) {
  MPI_Init(NULL, NULL);
  /* Find out rank*/
  int root = 0;
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int number, number4;
  /*root get user input, send to other processor*/
  if (world_rank == root) {
    printf( "Enter a value: ");
    if (scanf("%d", &number) == 1)
      {
        printf("You entered %d\n", number);
        int i;
        for (i = 1; i < world_size; i++){

            MPI_Send (&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
      }
    else {
      printf("Failed to read\n");
    }
  }

  /*other processor recieve data from root processor*/
  else {
    MPI_Recv (&number, 1, MPI_INT, root, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    number4 = number * world_rank;
    printf("Process rank %d received number %d from process 0, and multiply its rank to get %d\n",
           world_rank, number, number4);
  }



  MPI_Finalize();
  return 0;
  }
