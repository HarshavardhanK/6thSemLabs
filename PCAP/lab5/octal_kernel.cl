


__kernel void octal(__global int* A, __global int* B) {
	int i = get_global_id(0);

	int octal_number = 0, i = 1;
	int decimal_number = A[i];

    while (decimal_number != 0) {
        octal_number += (decimal_number % 8) * i;
        decimal_number /= 8;
        i *= 10;
    }

    B[i] = octal_number;
	
}