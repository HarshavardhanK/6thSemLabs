#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int ranked_power(int number, int rank) {

    if(rank % 2) {
        return number * number;
    }

    return number * number * number;
}

int main(int argc, char **argv) {

    if(argc < 2) {
        printf("Enter argument for size\n");
        return -1;
    }

    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int buffer[1000];
    MPI_Buffer_attach(buffer, 1000);

    if(!rank) {

        int size_arr = atoi(argv[1]);

        int array[size_arr];

        printf("Enter %d elements\n", size);

        for(int i = 0; i < size_arr; i++) {
            scanf("%d", &array[i]);
        }

        for(int i = 0; i < size_arr; i++) {
            MPI_Bsend((const void*) &array[i], 1, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
    }

    int num = 0;
    MPI_Recv((void*) &num, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, NULL);
    int res = ranked_power(num, rank);
    printf("Received %d from process %d | Result from process %d = %d\n", num, 0, rank, res);

    MPI_Finalize();

    return 0;
}