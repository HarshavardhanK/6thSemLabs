#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int fact(int n) {
    int f = 1;

    for(int i = 1; i <= n; i++) {
        f *= i;
    }

    printf("F of %d = %d\n",n, f);

    return f;
}

int fact2(int n) {

    int res = fact(n);

    return res * res;
}


int main(int argc, char **argv) {

    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int fact_ = fact(rank);
    int sum = 0;
    int all_sum = 0;

    MPI_Reduce(&fact_, &sum, 1, MPI_INT, MPI_SUM, 3, MPI_COMM_WORLD);
    MPI_Allreduce(&fact_, &all_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if(rank == 3) {
        printf("Sum is %d\n", sum);
        printf("All reduce sum is %d\n", all_sum);
    }

    MPI_Finalize();

    return 0;
}