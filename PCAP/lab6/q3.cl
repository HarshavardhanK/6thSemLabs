__kernel void odd(__global int* A) {

	int id = get_global_id(0);

	int size = get_global_size(0);

	if(id % 2 == 1 && id + 1 < size) {
		int temp = A[id];
		A[id] = A[id + 1];
		A[id + 1] = temp;
	}

}

__kernel void even(__global int* A) {

	int id = get_global_id(0);
	int size = get_global_size(0);

	if(id % 2 == 0 && id + 1 < size) {
		int temp = A[id];
		A[id] = A[id + 1];
		A[id + 1] = temp;
	}

}