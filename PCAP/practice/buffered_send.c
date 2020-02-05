#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    int pid;
    int n_proc;

    //pass address of the array (pointer to pointer)

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

    int buff[100];
    MPI_Buffer_attach(buff, 100);

    int size = atoi(argv[1]);

    //Attach buffer before any process starts

    if(pid == 0) {

        for(int i = 0; i < size; i++) {
            scanf("%d", &buff[i]);
        }

        printf("Sending array to process 1\n");

        MPI_Bsend(buff, 5, MPI_INT, 1, 1, MPI_COMM_WORLD);

    } else if(pid == 1) {
        int recv_buff[10];

        MPI_Recv(recv_buff, 5, MPI_INT, 0, 1, MPI_COMM_WORLD, NULL);

        for(int i = 0; i < size; i++) {
            printf("%d ", recv_buff[i]);
        }
    }

    printf("\n");
    MPI_Finalize();

    return 0;
}