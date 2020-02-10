__kernel void vector_complement(__global int *A, __global int *B){

	int i = get_global_id(0);
	int n = A[i];

    int dec = 0, i = 0, rem;
    while (n != 0) {
        rem = n % 10;
        dec = (dec*10) + rem;
        n = n/10;
    } 

    B[i] = dec;
}