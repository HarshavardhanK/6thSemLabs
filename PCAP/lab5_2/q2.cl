__kernel void invert_binary(__global int * A, __global int * C) {
	//Get the index of the current work item
	int i = get_global_id(0);
	//Do the operation
	int mul = 1;
	C[i] = 0;
	do {
		int r = A[i] % 10;
		A[i] = A[i] / 10;
		C[i] += (1 ^ r) * mul;
		mul *= 10;
	} while (A[i] > 0);
}