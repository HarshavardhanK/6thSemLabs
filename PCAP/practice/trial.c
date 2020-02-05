#include <mpi.h>
#include <stdio.h>

int main() {

    MPI_Init(NULL, NULL);
    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Rank: %d\n", rank);
    printf("No. of processes: %d\n", size);

    MPI_Finalize();

    return 0;
}