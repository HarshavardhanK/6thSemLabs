__kernel void decimal_to_octal(__global int * A, __global int * C) {
	//Get the index of the current work item
	int i = get_global_id(0);
	//Do the operation
	int mul = 1;
	C[i] = 0;
	while (A[i] > 0) {
		int r = A[i] % 8;
		A[i] = A[i] / 8;
		C[i] += r * mul;
		mul *= 10;
	}


}