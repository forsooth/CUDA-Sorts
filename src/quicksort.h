#ifndef QUICKSORT
#define QUICKSORT

#include "structs.h"

void quicksort(Data *data);
void quicksort_int(int *a, int p, int r);
void quicksort_float(float *a, int p, int r);
int partition_int(int* a, int p, int r);
int partition_float(float* a, int p, int r);

#endif
