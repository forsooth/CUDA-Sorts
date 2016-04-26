#ifndef PARALLEL_MERGESORT
#define PARALLEL_MERGESORT

#include "structs.h"
#include <stdio.h>

__global__ void merge_int(int *input, int *output, long unsigned int length, long unsigned int size);
__global__ void merge_float(float *input, float *output, long unsigned int length, long unsigned int size);
void parallel_merge_sort_int(Data *data);
void parallel_merge_sort_float(Data *data);
void parallel_merge_sort(Data *data);


#endif
