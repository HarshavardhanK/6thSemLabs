#include "mpi.h"
#include <stdio.h>

int main() {

	int num_proc;
	int proc_id;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

	if(!proc_id) {

		int num;
		printf("Send num: ");
		scanf("%d", &num);

		for(int i = 1; i < 4; i++) {
			MPI_Send(&num, 1, MPI_INT, i, 10, MPI_COMM_WORLD);
		}

	} else {

		int num;

		MPI_Recv(&num, 1, MPI_INT, MPI_ANY_SOURCE, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Received: %d\n", num);
	}

	MPI_Finalize();

	return 0;
}