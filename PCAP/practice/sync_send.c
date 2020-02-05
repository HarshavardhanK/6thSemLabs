#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define ROOT 0

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int pid; int n_proc;

    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

    char str[100];

    if(pid == ROOT) {

        strcpy(str, argv[1]);
        printf("string is: %s\n", str);

        int len = strlen(str);

        MPI_Ssend(&len, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Ssend(str, strlen(str), MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        
    } else if(pid == 1) {

        int len = 0;
        MPI_Recv(&len, 1, MPI_INT, ROOT, 1, MPI_COMM_WORLD, NULL);

        printf("Received string length is: %d\n", len);

        char recv[len];

        MPI_Recv(recv, len, MPI_CHAR, ROOT, 0, MPI_COMM_WORLD, NULL);

        printf("Received string is: %s\n", recv);
    }

    MPI_Finalize();

    return 0;
}