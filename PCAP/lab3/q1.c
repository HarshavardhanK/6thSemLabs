#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

//#define MPI_COMM_WORLD MCW

int factorial(int n) {
	int fact = 1;

	for(int i = 1; i <=n; i++)
		fact *= i;

	return fact;
}

int main(int argc, char** argv) {

	//printf("%d\n", factorial(atoi(argv[1])));

	int num_proc;
	int proc_id;

	int buff[num_proc];
	int temp_buff[num_proc];

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

	if(proc_id == 0) {

		printf("Enter numbers\n");

		for(int i = 0; i < num_proc; i++) {
			scanf("%d", &buff[i]);
		}

	}

	int num = 0;

	MPI_Scatter(&buff, 1, MPI_INT, &num, 1, MPI_INT, 0, MPI_COMM_WORLD);

	num = factorial(num);

	MPI_Gather(&num, 1, MPI_INT, temp_buff, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(proc_id == 0) {
		//printf("Result gathered is: %d\n", num);

		int sum = 0;

		for(int i = 0; i < num_proc; i++) {
			sum += temp_buff[i];
		}

		printf("Result is: %d\n", sum);
	}

	MPI_Finalize();



	return 0;
}