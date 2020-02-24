__kernel void even(__global int * A) {
	//Get the index of the current work item
	int id = get_global_id(0);
	int n = get_global_size(0);
	if (id % 2 == 0 && id+1 != n)
		if (A[id] > A[id+1]) {
			int temp = A[id];
			A[id] = A[id+1];
			A[id+1] = temp;
		}	
}