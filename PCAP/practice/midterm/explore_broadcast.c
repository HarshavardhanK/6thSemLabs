#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    int rank;
    int size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int arr[3];
    int n;

    if(!rank) {
        int size_arr = 3;
        // = {13, 445, 67};
        arr[0] = 13; arr[1] = 45; arr[2] = 456;
        n = 12;
    }

    MPI_Bcast(arr, 3, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 0; i < 3; i++) {
        printf("%d\n", arr[i]);
    }

    printf("N = %d FROM process %d\n", n, rank);

    MPI_Finalize();

    return 0;
    
}