#ifndef PARALLELRADIXSORT
#define PARALLELRADIXSORT

#include "structs.h"
#include <thrust/sort.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/execution_policy.h>
#include <time.h>

void parallel_radix_sort(Data *data);
void parallel_radix_sort_int(Data *data);
void parallel_radix_sort_float(Data *data);

#endif
