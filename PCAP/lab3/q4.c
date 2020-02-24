#include "mpi.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]){ 

	int rank,size,n;

	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	char str1[100],str2[100],r_str1[100],r_str2[100],r_comb[100];

	if (rank == 0) {

		fprintf(stdout, "Enter 2 strings: ");
		fflush(stdout);

		scanf("%s",str1);
		//scanf("\n");
		scanf("%s",str2);

		n = strlen(str1)/size;
	}

	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(str1,n,MPI_CHAR,r_str1,n,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Scatter(str2,n,MPI_CHAR,r_str2,n,MPI_CHAR,0,MPI_COMM_WORLD);

	char comb[2*n + 1];

	for (int i = 0; i < n; i++) {
		comb[2 * i] = r_str1[i];
		comb[2 * i + 1] = r_str2[i];
	}

	MPI_Gather(comb,2*n,MPI_CHAR,r_comb,2*n,MPI_CHAR,0,MPI_COMM_WORLD);

	if (rank == 0) {

		fprintf(stdout, "The final string is %s\n", r_comb);	
		fflush(stdout);

	}

	MPI_Finalize();
	return 0;
}