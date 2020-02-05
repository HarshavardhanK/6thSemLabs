#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>

#define MAX_LEN 300000

void init() {

	//create two input vectors
	int size;
	printf("Enter list size: ");
	scanf("%d", &size);

	int* A =(int*) malloc(sizeof(int) * size);
	int* B = (int*) malloc(sizeof(int) * size);

	for(int i = 0; i < size; i++) {
		A[i] = i;
	}

	for(int i = 0; i < size; i++) {
		B[i] = i + 1;
	}

	FILE* fp;
	char* src_str;

	fp = fopen("./vector_kernel.cl", "r");

	if(!fp) {
		printf("Error reading file\n");
		return;
	}

	src_str = (char*) malloc(sizeof(char) * MAX_LEN);
	size_t source_size = fread(src_str, 1, MAX_LEN, fp);

	fclose(fp);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;

	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	printf("Return is 46 %d\n", ret);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);
	printf("Return is 47 %d\n", ret);

	//Create an OpenCL context
	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	printf("Return is 53 %d\n", ret);

	//Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);
	printf("Return is 57 %d\n", ret);


	//Create memory buffers on the device for each of the vectors
	
	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, size * sizeof(int), NULL, &ret);
	printf("Return is 63 %d\n", ret);
	

	cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, size * sizeof(int), NULL, &ret);
	printf("Return is 67 %d\n", ret);
	cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size * sizeof(int), NULL, &ret);
	printf("Return is 69 %d\n", ret);

	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, size * sizeof(int), A, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, size * sizeof(int), B, 0, NULL, NULL);
	
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&src_str, (const size_t*) &source_size, &ret);

	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	printf("Return is %d\n", ret);

	cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);
	printf("Return is 80 %d\n", ret);

	//set the argumemts of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&c_mem_obj);

	size_t global_item_size = size;
	size_t local_item_size = 1;

	cl_event event;

	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);

	ret = clFinish(command_queue);

	int* C = (int*) malloc(sizeof(int) * size);

	ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, size * sizeof(int), C, 0, NULL, NULL);

	for(int i = 0; i < size; i++) {
		printf("%d + %d = %d\n", A[i], B[i], C[i]);
	}

}

int main() {

	init();

	return 0;
}