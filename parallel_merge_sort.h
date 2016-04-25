#ifndef PARALLEL_MERGESORT
#define PARALLEL_MERGESORT

#include "structs.h"
#include <stdio.h>

__global__ void mergeInt(int *input, int *output, long unsigned int length, long unsigned int size);
__global__ void mergeFloat(float *input, float *output, long unsigned int length, long unsigned int size);
void parallelMergeSortInt(Data *data);
void parallelMergeSortFloat(Data *data);
void parallelMergeSort(Data *data);


#endif
