#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

float average(float* arr, int n) {

	float avg = 0.0;

	for(int i = 0; i < n; i++) {
		avg += arr[i];
	}

	return avg / (float)n;

}

int main() {

	int num_proc;
	int proc_id;

	// = (int*) malloc(sizeof(int) * n);

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

	int m = 3;

	float arr[num_proc * m];
	float temp_arr[m];
	float rcv_arr[num_proc];// = NULL;

	if(!proc_id) {

		printf("Enter %d numbers: ", num_proc * m);

		for(int i = 0; i < num_proc * m; i++) {
			scanf("%f", &arr[i]);
		}

	}

	MPI_Bcast(&m , 1, MPI_INT, 0, MPI_COMM_WORLD);

	//temp_arr = (float*) malloc(sizeof(float) * m);

	printf("M: %d\n", m);

	MPI_Scatter(&arr, m, MPI_FLOAT, &temp_arr, m, MPI_FLOAT, 0, MPI_COMM_WORLD);

	//rcv_arr[proc_id] = average(temp_arr);
	float m_avg = average(temp_arr, m);

	//printf("Gathered average of proc: %d is %.2f\n", proc_id, m_avg);

	MPI_Gather(&m_avg, 1, MPI_FLOAT, rcv_arr, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

	if(proc_id == 0) {
		float avg = average(rcv_arr, num_proc);
		printf("Average of gathered average is: %.2f\n", avg);
	}

	MPI_Finalize();

	return 0;
}