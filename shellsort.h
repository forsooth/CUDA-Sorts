#ifndef SHELLSORT
#define SHELLSORT

#include "structs.h"
#include <stdio.h>

void shellsort(Data *data);

unsigned long long *generate_gaps(unsigned long long length);

void shellsort_int(Data *data);

void shellsort_float(Data *data);

#endif
