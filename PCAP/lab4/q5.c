#include<mpi.h>
#include<stdio.h>

void error_handler(int code) {

	if(code != MPI_SUCCESS) {
		char str[BUFSIZ];
		int err_len = 0;

		MPI_Error_string(code, str, &err_len);

		printf("%s\n", str);
	}
}

int main() {

	int rank, size;

	int error_code;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

	int error_code;

	int arr[100][size];
	int key;

	if(!rank){

		printf("Enter %d elements\n", size*size);
		for(int i=0;i<size;i++){

			for(int j=0;j<size;j++){

				scanf("%d", &arr[i][j]);
			}
		}
	}

	int recv[size];
	int recv_beta[size];
	int recv_beta2[size];
	
	for(int i=0;i<size;i++){

		error_code = MPI_Scatter(arr[i], 1, MPI_INT, &recv_beta[i], 1, MPI_INT, 0, MPI_COMM_WORLD);
		error_handler(error_code);
	}

	MPI_Alltoall(recv_beta, 1, MPI_INT, recv_beta2, 1, MPI_INT, MPI_COMM_WORLD);
	for(int i=0;i<size;i++){

		MPI_Scan(&recv_beta2[i], &recv[i], 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	}
		printf("Row %d: ", rank);

			for(int i=0;i<size;i++){

				printf("%d ", recv[i]);
			}

			printf("\n");	

	MPI_Finalize();
	return 0;
}
