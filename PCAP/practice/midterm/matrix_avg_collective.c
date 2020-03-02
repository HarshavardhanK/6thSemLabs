#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

float average(int* arr, int size) {
    float avg = 0.0;

    for(int i = 0; i < size; i++) {
        avg += (float)arr[i];
    }

    return avg / (float)(size);
}

int main(int argc, char** argv) {

    int size;
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int cols = atoi(argv[1]);

    int M;
    int mat[size][cols];

    float avg;

    if(!rank) {

        avg = 0.0;
        printf("Enter M\n"); 
        scanf("%d", &M);

        printf("Enter matrix\n");

        for(int i = 0; i < size; i++) {
            for(int j = 0; j < M; j++) {
                scanf("%d", &mat[i][j]);
            }
        }

    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int recv[M]; float avg_arr[M];
    MPI_Scatter(mat, M, MPI_INT, recv, M, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Recv\n");
    for(int i = 0; i < M; i++) {
        printf("%d ", recv[i]);
    }
    printf("\n");

    avg = average(recv, M);
    printf("Avg is %.2f\n", avg);

    MPI_Gather(&avg, 1, MPI_FLOAT, avg_arr, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if(!rank) {
        avg = 0.0;
        for(int i = 0; i < M; i++) {
            avg += avg_arr[i];
        }

        avg /= size;

        printf("Average of the matrix is: %.2f", avg);
    }

    MPI_Finalize();

    return 0;
}