#include <mpi.h>
#include <stdio.h>

void add(int* prev_row, int* curr_row, int size) {

}

int main() {

    int size;
    int rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int mat[3][3];

    if(!rank) {

        printf("Enter matrix\n");

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                scanf("%d", &mat[i][j]);
            }
            
        }
    }

    int recv[3];
    //MPI_Alltoall(mat, 3, MPI_INT, recv, 3, MPI_INT, MPI_COMM_WORLD);
    MPI_Allreduce(mat, recv, 3, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if(!rank) {
        for(int i = 0; i < 3; i++) {
                printf("%d ", recv[i]);
        }
    }
}