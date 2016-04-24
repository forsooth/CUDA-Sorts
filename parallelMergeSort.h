#ifndef PARALLEL_MERGESORT
#define PARALLEL_MERGESORT

#include "checkSortedness.h"

__global__ void mergeInt(int *input, int *output, long unsigned int length, long unsigned int size) {
    long unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;
    long unsigned int index1 = tid * size;
    long unsigned int index2 = index1 + size/2;
    long unsigned int end1 = index2 > length ? length : index2;
    long unsigned int end2 = index2 +  size/2 > length ? length : index2 + size/2;
    long unsigned int tmpIndex = index1;
  

    while (index1 < end1 && index2 < end2) {
        if (input[index1] <= input[index2]) {
            output[tmpIndex++] = input[index1++];
        } else {
            output[tmpIndex++] = input[index2++];
        }
    }
    
    while (index1 < end1) {
        output[tmpIndex++] = input[index1++];
    }
    while (index2 < end2) {
        output[tmpIndex++] = input[index2++];
    }
  
}

__global__ void mergeFloat(float *input, float *output, long unsigned int length, long unsigned int size) {
    long unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;
    long unsigned int index1 = tid * size;
    long unsigned int index2 = index1 + size/2;
    long unsigned int end1 = index2 > length ? length : index2;
    long unsigned int end2 = index2 +  size/2 > length ? length : index2 + size/2;
    long unsigned int tmpIndex = index1;
  

    while (index1 < end1 && index2 < end2) {
        if (input[index1] <= input[index2]) {
            output[tmpIndex++] = input[index1++];
        } else {
            output[tmpIndex++] = input[index2++];
        }
    }
    
    while (index1 < end1) {
        output[tmpIndex++] = input[index1++];
    }
    while (index2 < end2) {
        output[tmpIndex++] = input[index2++];
    }
  
}

void parallelMergeSortInt(Data *data);
void parallelMergeSortFloat(Data *data);

void parallelMergeSort(Data *data) {
    if (data->array_used == INT)
        parallelMergeSortInt(data);
    else
        parallelMergeSortFloat(data);
}

void parallelMergeSortInt(Data *data) {
    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, 0);
    unsigned int threads;
    long unsigned int size = 2;
    long unsigned int blocks;
    if (size * prop.maxThreadsDim[0] < data->length) {
        threads = prop.maxThreadsDim[0];
        blocks = data->length /(size * prop.maxThreadsDim[0]);
        if (blocks * size * threads < data->length) blocks += 1;
    } else {
        blocks = 1;
        threads = data->length/size;
        if (size * threads < data->length) threads += 1;
    }


    int *input, *tmp, *output;
    long unsigned int length = sizeof(int) * data->length;
    cudaMalloc((void**)&input, length);
    cudaMalloc((void**)&output, length);
    cudaMemcpy(input, data->intarray, length, cudaMemcpyHostToDevice);
    
    
    while (size/2 < data->length) {

        mergeInt<<<blocks, threads>>>(input, output, data->length, size);
        size = size * 2;
        if (size * prop.maxThreadsDim[0] < data->length) {
            threads = prop.maxThreadsDim[0];
            blocks = data->length /(size * prop.maxThreadsDim[0]);
            
            if (blocks * size * threads < data->length) blocks += 1;
        } else {
            blocks = 1;
            threads = data->length/size;
            if (size * threads < data->length) threads += 1;
        }
 
        tmp = input;
        input = output;
        output = tmp;
       
    }
 
    cudaMemcpy(data->intarray, input, length, cudaMemcpyDeviceToHost);
   
    checkSortedness(data);

}

void parallelMergeSortFloat(Data *data) {
    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, 0);
    unsigned int threads;
    long unsigned int size = 2;
    long unsigned int blocks;
    if (size * prop.maxThreadsDim[0] < data->length) {
        threads = prop.maxThreadsDim[0];
        blocks = data->length /(size * prop.maxThreadsDim[0]);
        if (blocks * size * threads < data->length) blocks += 1;
    } else {
        blocks = 1;
        threads = data->length/size;
        if (size * threads < data->length) threads += 1;
    }  

    float *input, *tmp, *output;
    long unsigned int length = sizeof(float) * data->length;
    cudaMalloc((void**)&input, length);
    cudaMalloc((void**)&output, length);
    cudaMemcpy(input, data->floatarray, length, cudaMemcpyHostToDevice);

    
    while (size/2 < data->length) {
printf("blocks %lu, threads %u, size %lu\n", blocks, threads, size);
  
        mergeFloat<<<blocks, threads>>>(input, output, data->length, size);
  
        size = size * 2;
        if (size * prop.maxThreadsDim[0] < data->length) {
            threads = prop.maxThreadsDim[0];
            blocks = data->length /(size * prop.maxThreadsDim[0]);
            
            if (blocks * size * threads < data->length) blocks += 1;
        } else {
            blocks = 1;
            threads = data->length/size;
            if (size * threads < data->length) threads += 1;
        }

        tmp = input;
        input = output;
        output = tmp;
       
    }
 
    cudaMemcpy(data->floatarray, input, length, cudaMemcpyDeviceToHost);
   
    checkSortedness(data);

}





#endif
