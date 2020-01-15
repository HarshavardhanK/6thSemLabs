#include "mpi.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main() {

	int proc_id;
	int num_proc;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

	int ar[100];// = (int*) malloc(sizeof(int) * 100);
	MPI_Buffer_attach(&ar, 100);


	if(!proc_id) {

		int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

		for(int i = 1; i < 10; i++) {
			//ar = arr[i];
			MPI_Bsend(&arr[i], 1, MPI_INT, i, i, MPI_COMM_WORLD);
			printf("sent to %d\n", i);
		}

	} else if(proc_id % 2 == 0) {

		int ar;// = (int*) malloc(sizeof(int) * 10);

		MPI_Recv(&ar, 1, MPI_INT, 0, proc_id, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		printf("%.2f\n", pow(ar, 2));

	} else {

		int ar;// = (int*) malloc(sizeof(int) * 10);

		MPI_Recv(&ar, 1, MPI_INT, 0, proc_id, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		printf("%.2f\n", pow(ar, 3));
	}


	MPI_Finalize();

	return 0;
}