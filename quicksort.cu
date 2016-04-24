/*        OVERVIEW: QuickSort implementation, using CLRS psudo-code
 *        DATE: April 18
 *         Behnam Heydarshahi, Matt Asnes, Xu Liu
 *
 */

#include <stdio.h>
#include "structs.h"

void quicksort(Data *data, Data_info *data_info);
void quicksort_int(int *a, int p, int r);
void quicksort_float(float *a, int p, int r);
int partition_int(int* a, int p, int r);
int partition_float(float* a, int p, int r);

/*
 *      To sort all array, call A, 1, length[A]
 */
void quicksort(Data *data) 
{
        if (data->array_used == INT) {
                quicksort_int(data->intarray, 0, data->length - 1);
        } else if (data->array_used == FLOAT) {
                quicksort_float(data->floatarray, 0, data->length - 1);
        } 
}


void quicksort_int(int *a, int p, int r)
{
	if(p < r) {
		int q = partition_int(a, p, r);
                quicksort_int(a, p, q-1);
	        quicksort_int(a, q+1, r);
	}
}

int partition_int(int* a, int p, int r)
{
        int x = a[r];
	int i = p-1;
	for(int j=p; j <r; j++) {
	        if(a[j] <= x) {
	                int temp= a[i];
			a[i]= a[j];
			a[j]= temp;
	        }
	}
	int temp= a[i+1];
	a[i+1] = a[r];
	a[r]= temp;
	return i+1;
}


void quicksort_float(float *a, int p, int r)
{
	if(p < r) {
		int q = partition_float(a, p, r);
                quicksort_float(a, p, q-1);
	        quicksort_float(a, q+1, r);
	}
}

int partition_float(float* a, int p, int r)
{
        int x = a[r];
	int i = p-1;
	for(int j=p; j <r; j++) {
	        if(a[j] <= x) {
	                float temp= a[i];
			a[i]= a[j];
			a[j]= temp;
	        }
	}
	int temp= a[i+1];
	a[i+1] = a[r];
	a[r]= temp;
	return i+1;
}
