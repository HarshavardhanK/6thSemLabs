__kernel void swap(__global int * A) {
	//Get the index of the current work item
	int id = get_global_id(0);
	//Do the operation
	id *= 2;
	int temp = A[id];
	A[id] = A[id + 1];
	A[id + 1] = temp;
}