#include <mpi.h>
#include <stdio.h>
#include <string.h>

void operation(int rank, int curr_index, char* res_buf, char char_at) {
    int i;
    for(i = 0; i <= rank; i++) {
        res_buf[i] = char_at;
    }

    res_buf[i] = '\0';
    printf("%s\n", res_buf);
}

int main() {

    int rank;
    int size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char str[100];
    int str_len;
    char recv_str[100];
    char output[200];

    if(!rank) {

        printf("Enter string\n");
        scanf("%s", str);

        str_len = strlen(str);
    }

    MPI_Bcast(&str_len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    char char_at;
    MPI_Scatter(str, 1, MPI_CHAR, &char_at, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    int curr_ind = (rank) * (rank + 1) / 2;
    printf("Curr ind = %d | char at = %c | at process %d\n", curr_ind, char_at, rank);

    operation(rank, curr_ind, recv_str, char_at);

    MPI_Gather(recv_str, rank + 1, MPI_CHAR, output, rank + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    if(!rank) {
        int ind = (size - 1) * (size - 1);
        output[ind] = '\0';
        printf("res %s\n", output);
    }

    MPI_Finalize();

    return 0;

    

}