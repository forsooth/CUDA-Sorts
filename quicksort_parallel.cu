#include"quicksort_parallel.h"
#include<stdio.h>

#define MAX_DEPTH       16
#define INSERTION_SORT  32

////////////////////////////////////////////////////////////////////////////////
// Selection sort used when depth gets too big or the number of elements drops
// below a threshold.
////////////////////////////////////////////////////////////////////////////////
__device__ void selection_sort(int *data, int left, int right)
{
    for (int i = left ; i <= right ; ++i)
    {
        int min_val = data[i];
        int min_idx = i;

        // Find the smallest value in the range [left, right].
        for (int j = i+1 ; j <= right ; ++j)
        {
            int val_j = data[j];

            if (val_j < min_val)
            {
                min_idx = j;
                min_val = val_j;
            }
        }

        // Swap the values.
        if (i != min_idx)
        {
            data[min_idx] = data[i];
            data[i] = min_val;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Very basic quicksort algorithm, recursively launching the next level.
////////////////////////////////////////////////////////////////////////////////
__global__ void quicksort_parallel_int(int *data, int left, int right, int depth)
{
    // If we're too deep or there are few elements left, we use an insertion sort...
    if (depth >= MAX_DEPTH || right-left <= INSERTION_SORT)
    {
        selection_sort(data, left, right);
        return;
    }

    int *lptr = data+left;
    int *rptr = data+right;
    int  pivot = data[(left+right)/2];

    // Do the partitioning.
    while (lptr <= rptr)
    {
        // Find the next left- and right-hand values to swap
        int lval = *lptr;
        int rval = *rptr;

        // Move the left pointer as long as the pointed element is smaller than the pivot.
        while (lval < pivot)
        {
            lptr++;
            lval = *lptr;
        }

        // Move the right pointer as long as the pointed element is larger than the pivot.
        while (rval > pivot)
        {
            rptr--;
            rval = *rptr;
        }

        // If the swap points are valid, do the swap!
        if (lptr <= rptr)
        {
            *lptr++ = rval;
            *rptr-- = lval;
        }
    }

    // Now the recursive part
    int nright = rptr - data;
    int nleft  = lptr - data;

    // Launch a new block to sort the left part.
    if (left < (rptr-data))
    {
        cudaStream_t s;
        cudaStreamCreateWithFlags(&s, cudaStreamNonBlocking);
        quicksort_parallel_int<<< 1, 1, 0, s >>>(data, left, nright, depth+1);
        cudaStreamDestroy(s);
    }

    // Launch a new block to sort the right part.
    if ((lptr-data) < right)
    {
        cudaStream_t s1;
        cudaStreamCreateWithFlags(&s1, cudaStreamNonBlocking);
        quicksort_parallel_int<<< 1, 1, 0, s1 >>>(data, nleft, right, depth+1);
        cudaStreamDestroy(s1);
    }
}


void quicksort_parallel(Data* data) {

       if (data->array_used == INT) {
	        clock_t begin, end;
	        double time_spent;
	        begin = clock();

    		int left = 0;
		int right = data->length-1;
		printf("Launching kernel on the GPU");
		quicksort_parallel_int<<< 1, 1 >>>(data->intarray, left, right, 0);
		checkCudaErrors(cudaDeviceSynchronize());
	        end = clock();
	        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	        fprintf(stdout, "Parallel Quicksort time: %f\n", time_spent);

        } else if (data->array_used == FLOAT) {//TODO: Add float support
	      //  clock_t begin, end;
	      //  double time_spent;
	      // begin = clock();

    		//int left = 0;
		//int right = data->length-1;
		//printf("Launching kernel on the GPU");
		//quicksort_parallel_float<<< 1, 1 >>>(data->floatarray, left, right, 0);
		//checkCudaErrors(cudaDeviceSynchronize());
	        //end = clock();
	        //time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	        //fprintf(stdout, "Parallel Quicksort time: %f\n", time_spent);
        }


    // Launch on device

    


	return 0;
}

