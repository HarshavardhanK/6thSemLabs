#include "mpi.h"

#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <ctype.h>

//USE MPI_Type_create_struct(....);


void send(char* word, int to_process) {

	printf("Sending %s\n", word);

	int status = MPI_Ssend(word, strlen(word), MPI_CHAR, to_process, 99, MPI_COMM_WORLD);

	if(status > 0) {
		printf("Successfully sent\n");
	}

}

void recv(char* word, int from_process) {

	int len = 0;

	MPI_Recv(&len, 1, MPI_INT, from_process, 98, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	word[len] = '\0';

	printf("Strlen is %d\n", len);

	MPI_Recv(word, 10, MPI_CHAR, from_process, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	for(int i = 0; i < len; i++) {

		if(islower(word[i])) {
			word[i] = toupper(word[i]);

		} else {
			word[i] = tolower(word[i]);
		}
	}

	printf("Received %s\n", word);

}

int main(int argc, char** argv) {

	int num_proc;
	int proc_id;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

	if(proc_id == 0) {

		char* word = (char*) malloc(sizeof(char) * 10);
		scanf("%s", word);

		int len = strlen(word);

		MPI_Ssend(&len, 1, MPI_INT, !proc_id, 98, MPI_COMM_WORLD);

		if(word) {
			send(word, !proc_id);

		} else {
			printf("No string\n");
		}

	} else {

		char* word = (char*) malloc(sizeof(char) * 10);
		recv(word, !proc_id);

	}

	MPI_Finalize();

	return 0;
}