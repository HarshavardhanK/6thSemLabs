#include <mpi.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int ascii_sum(char* str) {
	int sum = 0;
	int str_len = strlen(str);

	for(int i = 0; i < 4; i++) {
		if(isalpha(str[i])) {
			sum += str[i];
		}
	}

	return sum;
}

int col_prod(int A[4]) {
	int prod = 1;

	for(int i = 0; i < 4; i++) {
		prod *= A[i];
	}

	return prod;
}

int main(int argc, char** argv) {

	/*printf("%d\n", ascii_sum(argv[1], 0));*/

	int mat[4][4] = {{1, 2, 3, 2},
					{2, 3, 1, 4},
					{2, 1, 3, 2},
					{2, 4, 3, 5}};
	//printf("Prod = %d\n", col_prod(mat, 3));

	int rank;
	int size;

	char str[200];
	int prod_arr[4];
	int sum_arr[4];
	char sstr[4];
	int arr[4];
	int mmat[4][4];


	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(!rank) {
		printf("Enter string: ");
		scanf("%s", str);
		//transpose(mat);

		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				printf("%d ", mat[i][j]);
			}
			printf("\n");
		}

	}

	
	MPI_Scatter(mat, 4, MPI_INT, mmat, 4, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Alltoall(mmat, 1, MPI_INT, arr, 1, MPI_INT, MPI_COMM_WORLD);

	MPI_Scatter(str, 4, MPI_CHAR, sstr, 4, MPI_CHAR, 0, MPI_COMM_WORLD);
	

	int prod = col_prod(arr);
	int asci = ascii_sum(sstr);

	//printf("Rank %d col prod = %d\n", rank, prod);

	MPI_Gather(&asci, 1, MPI_INT, sum_arr, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Gather(&prod, 1, MPI_INT, prod_arr, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(!rank) {

		for(int i = 0; i < 4; i++) {
			printf("ASCII SUM %d from process %d\n", sum_arr[i], i);
			printf("COL PROD %d from process %d\n", prod_arr[i], i);

			printf("SUM %d FROM PROCESS %d\n", i, prod_arr[i] + sum_arr[i]);
		}
	}

	MPI_Finalize();

	return 0;

}