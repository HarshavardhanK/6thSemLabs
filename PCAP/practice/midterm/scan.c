#include <mpi.h>
#include <stdio.h>

int fact(int n) {
    if(n <= 1) {
        return 1;
    }

    return n * fact(n - 1);
}

int main() {

    int rank; int size;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int fact_ = fact(rank + 3);
    int sum = 0;

    MPI_Scan(&fact_, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if(rank == size - 1) {
        printf("Sum is %d\n", sum);
    }

    MPI_Finalize();

    return 0;

}