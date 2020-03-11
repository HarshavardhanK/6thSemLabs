#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int factorial(int num) {
    int f = 1;

    for(int i = 1; i <= num; i++) {
        f *= i;
    }

    return f;
}

void error_handler(int err_code) {

    if(err_code != MPI_SUCCESS) {
        char err_string[BUFSIZ];
        int str_len;

        MPI_Error_string(err_code, err_string, &str_len);
        printf("%s\n", err_string);
    }

}

void fact_gather() {

    int rank; int size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int fact_arr[size];
    int res[size];

    MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    int err;

    if(!rank) {
        for(int i = 0; i < size; i++) {
            fact_arr[i] = i + 1;
        }

        printf("Array is\n");
        for(int i = 0; i < rank; i++) {
            printf("%d ", fact_arr[i]);
        }

        printf("\n");
    }

    int num;
    err = MPI_Scatter(fact_arr, 1, MPI_INT, &num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int fact = factorial(num);

    MPI_Allgather(&fact, 1, MPI_INT, res, 1, MPI_INT, MPI_COMM_WORLD);

    //MPI_Gather(&fact, 1, MPI_INT, res, 1, MPI_INT, 0, MPI_COMM_WORLD); 
    //Gather collects the results in the specified 'root' process, in this case 0

    if(rank == 0) {
        printf("Res arr\n");
        for(int i = 0; i < size; i++) {
            printf("%d ", res[i]);
        }
        printf("\n");
    }

    MPI_Finalize();

}

char toggle(char c) {

    if(islower(c)) {
        return toupper(c);
    }

    return tolower(c);
}

void char_gather() {

    int rank; int size;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);


    char str[20];
    char output[20];
    char c;

    double start = MPI_Wtime();

    if(!rank) {

        strcpy(str, "Hell");
    }

    int err = MPI_Scatter(str, 1, MPI_CHAR, &c, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    error_handler(err);

    char m = toggle(c);

    err |= MPI_Gather(&m, 1, MPI_CHAR, output, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    error_handler(err);

    double end = MPI_Wtime();

    if(!rank) {
        output[size] = '\0';

        printf("Original string: %s | Output string: %s\n", str, output);
        printf("Time takenn is %fs\n", (end-start));
    }

    MPI_Finalize();

}

int main() {

    //fact_gather();
    char_gather();

    return 0;
}