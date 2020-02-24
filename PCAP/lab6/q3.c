// A complete program for vector addition

#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>

//Max source size of the kernel string
#define MAX_SOURCE_SIZE (0x100000)

int main(void) {
	//Create the two input vectors
	int i;

	int LIST_SIZE;
	printf("Enter how many elements:");
	scanf("%d",&LIST_SIZE);

	int * A = (int *)malloc(sizeof(int) * LIST_SIZE);

	//Initialize the input vectors
	for (i = 0; i < LIST_SIZE; i++) {
		A[i] = LIST_SIZE - i;
	}

	for (i = 0; i < LIST_SIZE; i++) {
		printf("%d ",A[i]);
	}	
	printf("\n");

	//Load the kernel source code into the array source_str
	FILE *fpo,*fpe;
	char * source_str_odd;
	char * source_str_even;
	size_t source_size_odd;
	size_t source_size_even;

	fpo = fopen("odd.cl","r");
	fpe = fopen("even.cl","r");

	if (!fpo || !fpe) {
		fprintf(stderr,"Failed to load kernel\n");
		getchar();
		exit(1);
	}
	source_str_odd = (char *)malloc(MAX_SOURCE_SIZE);
	source_size_odd = fread(source_str_odd,1,MAX_SOURCE_SIZE,fpo);

	source_str_even = (char *)malloc(MAX_SOURCE_SIZE);
	source_size_even = fread(source_str_even,1,MAX_SOURCE_SIZE,fpe);
	fclose(fpo);
	fclose(fpe);

	//Get platform and device information
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1,&platform_id,&ret_num_platforms);
	ret = clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_GPU,1,&device_id,&ret_num_devices);

	//Create an OpenCL context
	cl_context context = clCreateContext(NULL,1,&device_id,NULL,NULL,&ret);

	//Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context,device_id,NULL,&ret);

	//Create memory buffers on the device for each vector A,B and C
	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_WRITE,LIST_SIZE * sizeof(int),NULL,&ret);

	//Copy the lists A and B to their respective mem buffers
	ret = clEnqueueWriteBuffer(command_queue,a_mem_obj,CL_TRUE,0,LIST_SIZE * sizeof(int),A,0,NULL,NULL);

	//Create a program from the kernel source
	cl_program program_odd = clCreateProgramWithSource(context,1,(const char **)&source_str_odd,(const size_t *)&source_size_odd, &ret);
	cl_program program_even = clCreateProgramWithSource(context,1,(const char **)&source_str_even,(const size_t *)&source_size_even, &ret);

	//Build the program
	ret = clBuildProgram(program_odd,1,&device_id,NULL,NULL,NULL);
	ret = clBuildProgram(program_even,1,&device_id,NULL,NULL,NULL);

	//Create the OpenCL kernel object
	cl_kernel kernel_odd = clCreateKernel(program_odd,"odd",&ret);
	cl_kernel kernel_even = clCreateKernel(program_even,"even",&ret);

	//Set the arguments of the kernel
	ret = clSetKernelArg(kernel_odd,0,sizeof(cl_mem),(void *)&a_mem_obj);
	ret = clSetKernelArg(kernel_even,0,sizeof(cl_mem),(void *)&a_mem_obj);


	//Execute the OpenCL kernel on the array
	size_t global_item_size = LIST_SIZE;
	size_t local_item_size = 1;

	//Execute the kernel on the device
	cl_event event;

	for (i = 0; i < LIST_SIZE/2; i++) {
		ret = clEnqueueNDRangeKernel(command_queue,kernel_odd,1,NULL,&global_item_size,&local_item_size,0,NULL,NULL);
		ret = clEnqueueNDRangeKernel(command_queue,kernel_even,1,NULL,&global_item_size,&local_item_size,0,NULL,NULL);
	}

	

	ret = clFinish(command_queue);

	int * C = (int *)malloc(sizeof(int) * LIST_SIZE);

	//read the mem buffer C on the device to the local variable C
	ret = clEnqueueReadBuffer(command_queue,a_mem_obj,CL_TRUE,0,LIST_SIZE * sizeof(int),A,0,NULL,NULL);

	printf("\nSorted:\n");

	//Display the result to the screen
	for (i = 0; i < LIST_SIZE; i++)
		printf("%d ",A[i]);

	printf("\n");

	//Clean up
	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel_odd);
	ret = clReleaseKernel(kernel_even);
	ret = clReleaseProgram(program_odd);
	ret = clReleaseProgram(program_even);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	free(A);
	getchar();
	return 0;
}
