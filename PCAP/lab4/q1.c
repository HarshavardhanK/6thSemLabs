#include <mpi.h>
#include <stdio.h>

long int factorial(int num) {

	if(num <= 1) {
		return 1;
	}

	return num * factorial(num - 1);
}

int main(int argc, char** argv) {

	int pid;
	int n_proc;

	long long unsigned int receive_buffer;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &n_proc);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	long long unsigned int fact = factorial(pid + 1);

	MPI_Scan(&fact, &receive_buffer, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	if(pid == n_proc - 1) {
		printf("Result: %lld\n", receive_buffer);
	}

	MPI_Finalize();

	return 0;
}