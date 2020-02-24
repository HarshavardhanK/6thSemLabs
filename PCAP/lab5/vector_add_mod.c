#include <OpenCL/CL.h>
#include <stdio.h>
#include <stdlib.h>

char* get_kernel_source(char* path) {

    FILE* fp = fopen(path, "r");

    if(!fp) {
        printf("ERROR: No such kernel file\n");
        return NULL;
    }

    char* source_str = (char*) malloc(sizeof(char) * 10000);
    size_t size = fread(source_str, 1, 1000, fp);

    fclose(fp);

    return source_str;
}

void get_context_and_command_queue(cl_context *return_context, cl_command_queue *return_command_queue, cl_device_id** device_id) {

    cl_int ret;

    //Get platform ID
    cl_uint num_platforms = 1;
    
    if((ret = clGetPlatformIDs(0, NULL, &num_platforms)) < 0) {
        return;
    }

    cl_platform_id *platform_id = (cl_platform_id*) malloc(sizeof(cl_platform_id) * num_platforms);

    if((ret = clGetPlatformIDs(num_platforms, platform_id, NULL)) < 0) {
        printf("Error getting platform ID\n");
        return;
    }

    if(ret < 0) {
        printf("Error in obtaining platforms\n");
        return;
    }

    cl_uint num_devices = 1;
    
    if((ret = clGetDeviceIDs(platform_id[0], CL_DEVICE_TYPE_CPU, 0, NULL, &num_devices)) < 0) {
        printf("Error getting num devices\n");
        return;
    }

    //cl_device_id *device_id = (cl_device_id*) malloc(sizeof(cl_device_id) * num_devices);

    if((ret = clGetDeviceIDs(platform_id[0], CL_DEVICE_TYPE_CPU, num_devices, *device_id, NULL)) < 0) {
        printf("Error getting deivce IDs\n");
        return;
    }

    *return_context = clCreateContext(NULL, 1, *device_id, NULL, NULL, &ret);

    if(ret < 0) {
        printf("Error in getting creating context\n");
        return;
    }

    *return_command_queue = clCreateCommandQueue(*return_context, (*device_id)[0], 0, &ret);

    if(ret < 0) {
        printf("Error in creating command queue\n");
        return;
    }

    printf("Successfully created context and command queue\n");

}

void create_memory_objects(cl_command_queue command_queue, cl_context context, cl_mem* memA, cl_mem* memB, cl_mem* memC, int* A, int* B, unsigned int size) {

    cl_int ret;

    *memA = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int) * size, NULL, &ret);

    if(ret < 0) {
        printf("Error creating buffer\n");
        return;
    }

    *memB = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int) * size, NULL, &ret);

    *memC = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * size, NULL, &ret);

    if(ret < 0) {
        printf("Error creating buffer\n");
        return;
    }

    if((ret = clEnqueueWriteBuffer(command_queue, *memA, CL_TRUE, 0, sizeof(A), A, 0, NULL, NULL)) < 0) {
        printf("Error writing A into memA\n");
        return;
    }

    if((ret = clEnqueueWriteBuffer(command_queue, *memB, CL_TRUE, 0, sizeof(B), B, 0, NULL, NULL)) < 0) {
        printf("Error writing B into memB\n");
        return;
    }

    printf("Successfully created memory buffers\n");
}

cl_kernel create_kernel_with(cl_context context, cl_uint num_devices, cl_device_id *devices, cl_mem memA, cl_mem memB, cl_mem memC) {

    cl_int ret;

    cl_kernel kernel;

    const char* str = get_kernel_source("./vector_kernel.cl");

    cl_program program = clCreateProgramWithSource(context, 1, &str, NULL, &ret);

    if(ret < 0) {
        printf("ERROR: In creating program with source\n");
        
    } else {

        ret = clBuildProgram(program, num_devices, devices, NULL, NULL, NULL);

        if(ret < 0) {
            printf("ERROR: In building program\n");
            return NULL;
        }

        kernel = clCreateKernel(program, "vector_add", &ret);

        if(ret < 0) {
            printf("ERROR: Creating kernel\n");
            return NULL;
        }

        if((ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), &memA)) < 0) {
            printf("ERROR: Setting argument 1\n");
        }

        if((ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), &memB)) < 0) {
            printf("ERROR: Setting argument 1\n");
        }

        if((ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), &memC)) < 0) {
            printf("ERROR: Setting argument 1\n");
        }

    }

    return kernel;

}

int main(int argc, char** argv) {

    if(argc < 2) {
        return -1;
    }

    int size = atoi(argv[1]);

    int* A = (int*) malloc(sizeof(int) * size);
    int* B = (int*) malloc(sizeof(int) * size);

    //output vector
    int* C = (int*) malloc(sizeof(int) * size);

    for(int i = 0; i < size; i++) {
        A[i] = i * i + 1;
        B[i] = i * i - i;
    }

    cl_context context;
    cl_command_queue command_queue;

    cl_mem memA, memB, memC;
    cl_int ret;

    cl_device_id* devices = (cl_device_id*) malloc(sizeof(cl_device_id) * 1);

    get_context_and_command_queue(&context, &command_queue, &devices);
    create_memory_objects(command_queue, context, &memA, &memB, &memC, A, B, size);

    size_t global_size = size;
    size_t local_size = 1;

    

    cl_kernel kernel = create_kernel_with(context, 1, devices, memA, memB, memC);

    if((ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL)) < 0) {
        printf("ERROR: Enqueueing ND Range kernel\n");
        return -1;
    }

    if((ret = clFinish(command_queue)) < 0) {
        printf("ERROR: Finishing\n");
        return -1;
    }

    if((ret = clEnqueueReadBuffer(command_queue, memC, CL_TRUE, 0, sizeof(C), C, 0, NULL, NULL)) < 0) {
        printf("ERROR: Reading data object from memory\n");
        return -1;
    }

    ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	/*ret = clReleaseProgram(program);
	ret = clReleaseMemObject(s_mem_obj);
	ret = clReleaseMemObject(res_mem_obj);*/
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

    for(int i = 0; i < size; i++) {
        printf("%d + %d = %d\n", A[i], B[i], C[i]);
    }

    printf("\n");


    return 0;


}