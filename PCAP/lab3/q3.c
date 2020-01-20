
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vowels(char* str, int len) {
	int vow = 0;

	for(int i = 0; i < len; i++) {
		if(!(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')) {
			vow++;
		}
	}

	return vow;
}

int main() {

	char str[100];
	char temp[100];

	int arr[20];

	int num_proc;
	int proc_id;

	int m;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

	if(!proc_id) {
		printf("Enter string: ");
		scanf("%s", str);

		if(strlen(str) % num_proc != 0) {
			return -1;
		}

		m = strlen(str) / num_proc;
	}

	MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Scatter(&str, m, MPI_CHAR, &temp, m, MPI_CHAR, 0, MPI_COMM_WORLD);

	int vows = vowels(temp, m);

	MPI_Gather(&vows, 1, MPI_INT, arr, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

	if(proc_id == 0) {
		int vows_ = 0;

		for(int i = 0; i < num_proc; i++) {
			vows_ += arr[i];
		}

		printf("No. of non-vowels: %d\n", vows_);
	}

	MPI_Finalize();

	return 0;


}