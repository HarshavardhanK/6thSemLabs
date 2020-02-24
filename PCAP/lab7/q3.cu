
#include <stdio.h>

__global__ void thread_per(int* a, int * b, int *c, int* alpha) {
	int index = threadIdx.x + blockIdx.x * blockDim.x;
	c[index] = *alpha * a[index] + b[index];
}

void thread_per_block(int count) {

	int *a = (int*) malloc(sizeof(int) * count);
	int *b = (int*) malloc(sizeof(int) * count);
	int *c = (int*) malloc(sizeof(int) * count);

	int alpha;

	printf("Enter alpha: ");
	scanf("%d", &alpha);

	int *d_a;
	int *d_b;
	int *d_c;
	int *d_alpha;

	for(int i = 0; i < count; i++) {
		a[i] = i;
		b[i] = i + 2;
	}

	cudaMalloc((void **)& d_a, sizeof(int) * count);
	cudaMalloc((void **)& d_b, sizeof(int) * count);
	cudaMalloc((void **)& d_c, sizeof(int) * count);
	cudaMalloc((void **) &d_alpha, sizeof(int));

	cudaMemcpy(d_a, a, count * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, count * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_alpha, &alpha, sizeof(int), cudaMemcpyHostToDevice);
	
	thread_per<<<ceil(count / 256.0), 256>>>(d_a, d_b, d_c, d_alpha);

	cudaMemcpy(c, d_c, sizeof(int) * count, cudaMemcpyDeviceToHost);

	for(int i = 0; i < count; i++) {
		printf("%d * %d + %d = %d\n", alpha, a[i], b[i], c[i]);
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