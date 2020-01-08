#include "mpi.h"

#include <iostream>
#include <cmath>

using namespace std;

bool is_prime(int number) {

	float num_sqrrt = sqrt(number);

	for(int i = 2; i < num_sqrrt; i++) {

		if(number % i == 0) {
			return false;
		}
	}

	return true;
}

int main() {

	int num_proc;
	int proc_id;

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

	if(proc_id == 0) {

		for(int i = 0; i < 50; i++) {

			if(is_prime(i)) {
				cout << i << " is prime\n";
			}
		}

	} else if(proc_id == 1) {

		for(int i = 50; i < 100; i++) {

			if(is_prime(i)) {
				cout << i << " is prime\n";
			}
		}
	}

	MPI_Finalize();

	return 0;
}