#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int occurences(int* arr, int key, int size) {
	int count = 0;

	for(int i = 0; i < size; i++) {
		if(arr[i] == key) {
			count++;
		}
	}

	return count;
}

int main(int argc, char** argv) {


	int pid;
	int n_proc;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &n_proc);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	int num;

	int matrix[3][3];

	if(!pid) {

		printf("Enter matrix\n");

		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				scanf("%d", &matrix[i][j]);
			}
		}

		printf("Enter element to search: ");
		scanf("%d", &num);

	}

	MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int rows[3]; int count;

	MPI_Scatter(matrix, 3, MPI_INT, rows, 3, MPI_INT, 0, MPI_COMM_WORLD);

	int occ = occurences(rows, num, 3);

	MPI_Scan(&occ, &count, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	if(pid == n_proc - 1) {
		printf("Count is: %d\n", count);
	}

	MPI_Finalize();

	return 0;

}