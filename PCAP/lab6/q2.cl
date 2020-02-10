__kernel void sort(__global int * A, __global int * res) {

	int id = get_global_id(0);
	int n = get_global_size(0);
	
	int position = 0;

	for (int i = 0; i < n; i++)
		if (A[i] < A[id] || (A[i] == A[id] && i < id))
			position++;

	res[position] = A[id];		
}