#include "mpi.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int rank,size,N,s_arr[100],r_arr[100],sum_sub_arr[100];
	int sum_arr[100];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if (rank == 0) {
		int n;
		fprintf(stdout, "Enter n: ");
		fflush(stdout);
		scanf("%d",&n);
		fprintf(stdout, "Enter %d elements:\n",n);
		fflush(stdout);
		for (int i = 0; i < n; i++) {
			scanf("%d",&s_arr[i]);
		}
		N = n / 4;
	}
	MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(s_arr,N,MPI_INT,r_arr,N,MPI_INT,0,MPI_COMM_WORLD);
	sum_sub_arr[0] = r_arr[0];
	for (int i = 1; i < N; i++) {
		sum_sub_arr[i] = sum_sub_arr[i - 1] + r_arr[i];
	}
	MPI_Gather(sum_sub_arr,N,MPI_INT,sum_arr,N,MPI_INT,0,MPI_COMM_WORLD);
	if (rank == 0) {
		fprintf(stdout, "The resultant array is\n");
		fflush(stdout);
		for (int i = 0; i < N * size; i++)
			fprintf(stdout, "%d ", sum_arr[i]);
		fprintf(stdout, "\n");
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}