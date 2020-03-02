#include <stdio.h>

__global__ void vector_add(int* a, int* b, int* c) {
	c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}

void blocks(int count) {

	int *a = (int*) malloc(sizeof(int) * count);
	int *b = (int*) malloc(sizeof(int) * count);
	int *c = (int*) malloc(sizeof(int) * count);

	int *d_a;
	int *d_b;
	int *d_c;

	for(int i = 0; i < count; i++) {
		a[i] = i;
		b[i] = i + 2;
	}

	cudaMalloc((void **)& d_a, sizeof(int) * count);
	cudaMalloc((void **)& d_b, sizeof(int) * count);
	cudaMalloc((void **)& d_c, sizeof(int) * count);

	cudaMemcpy(d_a, a, count * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, count * sizeof(int), cudaMemcpyHostToDevice);
	
	vector_add<<<count, 256>>>(d_a, d_b, d_c);

	cudaMemcpy(c, d_c, sizeof(int) * count, cudaMemcpyDeviceToHost);

	for(int i = 0; i < count; i++) {
		printf("%d + %d = %d\n", a[i], b[i], c[i]);
	}


	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);

}

__global__ void thread_vect_add(int* a, int* b, int* c) {
	c[threadIdx.x] = a[threadIdx.x] + b[threadIdx.x];
}

void threads(int count) {

	int *a = (int*) malloc(sizeof(int) * count);
	int *b = (int*) malloc(sizeof(int) * count);
	int *c = (int*) malloc(sizeof(int) * count);

	int *d_a;
	int *d_b;
	int *d_c;

	for(int i = 0; i < count; i++) {
		a[i] = i;
		b[i] = i + 2;
	}

	cudaMalloc((void **)& d_a, sizeof(int) * count);
	cudaMalloc((void **)& d_b, sizeof(int) * count);
	cudaMalloc((void **)& d_c, sizeof(int) * count);

	cudaMemcpy(d_a, a, count * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, count * sizeof(int), cudaMemcpyHostToDevice);
	
	thread_vect_add<<<1, count>>>(d_a, d_b, d_c);

	cudaMemcpy(c, d_c, sizeof(int) * count, cudaMemcpyDeviceToHost);

	for(int i = 0; i < count; i++) {
		printf("%d + %d = %d\n", a[i], b[i], c[i]);
	}


	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);

}

__global__ void thread_per(int* a, int * b, int *c) {
	int index = threadIdx.x + blockIdx.x * blockDim.x;
	c[index] = a[index] + b[index];
}

void thread_per_block(int count) {

	int *a = (int*) malloc(sizeof(int) * count);
	int *b = (int*) malloc(sizeof(int) * count);
	int *c = (int*) malloc(sizeof(int) * count);

	int *d_a;
	int *d_b;
	int *d_c;

	for(int i = 0; i < count; i++) {
		a[i] = i;
		b[i] = i + 2;
	}

	cudaMalloc((void **)& d_a, sizeof(int) * count);
	cudaMalloc((void **)& d_b, sizeof(int) * count);
	cudaMalloc((void **)& d_c, sizeof(int) * count);

	cudaMemcpy(d_a, a, count * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, count * sizeof(int), cudaMemcpyHostToDevice);
	
	thread_per<<<ceil(count / 256.0), 256>>>(d_a, d_b, d_c);

	cudaMemcpy(c, d_c, sizeof(int) * count, cudaMemcpyDeviceToHost);

	for(int i = 0; i < count; i++) {
		printf("%d + %d = %d\n", a[i], b[i], c[i]);
	}

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
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