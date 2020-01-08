#include "mpi.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

void operation(int a, int b, int proc_id) {

	printf("Result is\n");

	if(proc_id == 0) {
		printf("%d + %d = %d\n", a, b, a + b);
	} else if(proc_id == 1) {
		printf("%d - %d = %d\n", a, b, a - b);
	} else if (proc_id == 2){
		printf("%d x %d = %d\n", a, b, a * b);

	} else if(proc_id == 3) {
		printf("%d / %d = %.2f\n", a, b, (float)a / (float)b);
	}

}

int main(int argc, char** argv) {

	int proc_id;
	int num_procs;

	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
	MPI_Comm_rank(MPI_COMM_WORLD, &num_procs);

	operation(a, b, proc_id);

	MPI_Finalize();

	return 0;


}