#include <stdio.h>

__global__ void thread_per(float* a, float * b) {
	int index = threadIdx.x + blockIdx.x * blockDim.x;
	b[index] = sinf(a[index]);
}

void thread_per_block(int count) {

	float a[] = {0.0, 1.57, 2.57, 3.14};
	float *b = (float*) malloc(sizeof(float) * 4);

	float *d_a;
	float *d_b;

	cudaMalloc((void **)& d_a, sizeof(float) * 4);
	cudaMalloc((void **)& d_b, sizeof(float) * 4);

	cudaMemcpy(d_a, a, count * sizeof(float), cudaMemcpyHostToDevice);
	
	thread_per<<<ceil(count / 256.0), 256>>>(d_a, d_b);

	cudaMemcpy(b, d_b, sizeof(float) * 4, cudaMemcpyDeviceToHost);

	for(int i = 0; i < count; i++) {
		printf("sin(%.2f) = %.2f\n", a[i], b[i]);
	}

	cudaFree(d_a);
	cudaFree(d_b);
}

int main(int argc, char** argv) {

	if(argc < 2) {
		printf("Enter count in file args\n");
		return -1;
	}

	int count = atoi(argv[1]);

	thread_per_block(count);

	return 0;

}
