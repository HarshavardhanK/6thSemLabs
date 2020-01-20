
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cross(char* str, char* str2, char* cross_) {
	int len = strlen(str);

	//char* cross_ = (char*) malloc(sizeof(char) * len * 2);

	int k = 0;
	int j = 0;

	for(int i = 0; i < 2 * len; i++) {

		if(i % 2 == 0) {
			cross_[i] = str[k++];

		} else {
			cross_[i] = str2[j++];
		}
	}

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

		printf("Enter string 1: ");
		scanf("%s", str);

		printf("Enter string 2: ");
		scanf("%s", temp);

		char* cross_ = (char*) malloc(sizeof(char) * 2 * strlen(str));

		cross(str, temp, cross_);

		printf("%s\n", cross_);
		

		if(strlen(str) % num_proc != 0) {
			return -1;
		}

		m = strlen(str) / num_proc;
	}

	//MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

	/*MPI_Scatter(&str, 1, MPI_CHAR, &temp, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

	//int vows = vowels(temp, m);

	MPI_Gather(&vows, 1, MPI_INT, arr, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

	if(proc_id == 0) {
		int vows_ = 0;

		for(int i = 0; i < num_proc; i++) {
			vows_ += arr[i];
		}

		printf("No. of non-vowels: %d\n", vows_);
	}*/

	MPI_Finalize();

	return 0;


}