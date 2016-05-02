
#include "even_odd_sort.h"
 
 
 
 
__global__ void even_sort(int* ary, int size)
{
	int tid = (blockIdx.z * gridDim.x * gridDim.y
                + blockIdx.y * gridDim.x
                + blockIdx.x) * blockDim.x + threadIdx.x;
	if(1 == (tid + 1 ) % 2) 
	{
		 
		if(ary[tid] > ary[tid + 1] && tid + 1 < size)
		{
			int tp = ary[tid];
			ary[tid] = ary[tid + 1];
			ary[tid + 1] = tp;
 
		}
	}
	__syncthreads();
 
}
__global__ void odd_sort(int* ary, int size)
{
	int tid = (blockIdx.z * gridDim.x * gridDim.y
                + blockIdx.y * gridDim.x
                + blockIdx.x) * blockDim.x + threadIdx.x;
	if(0 == (tid + 1 ) % 2) 
	{
 
		if(ary[tid] > ary[tid + 1] && tid + 1 < size)
		{
			int tp = ary[tid];
			ary[tid] = ary[tid + 1];
			ary[tid + 1] = tp;
 
		}
	}
	__syncthreads();
}
void even_odd_sort(Data *data)
{
	const int SIZE = data->length;
  
    int threads;
    Grid grid;
    int size = 1;
	cal_grid(&grid, &threads, data->length, size);	 
    dim3 blocks(grid.blockx, grid.blocky, grid.blockz);
    int* gary;
	cudaMalloc((void**) &gary, SIZE * sizeof(int));
	cudaMemcpy(gary, data->intarray, SIZE * sizeof(int), cudaMemcpyHostToDevice);
	for(int i = 0; i < SIZE; ++ i)
	{
	    if (i % 2 == 0) {
		    even_sort<<<blocks, threads>>>(gary, SIZE);
		} else {
		    odd_sort<<<blocks, threads>>>(gary, SIZE);
		}
	}
	 
	cudaMemcpy(data->intarray, gary, SIZE * sizeof(int), cudaMemcpyDeviceToHost);
	 
	cudaFree(gary);
	 
	 
}
