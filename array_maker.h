#ifndef ARRAYMAKER
#define ARRAYMAKER

#include "structs.h"

Data *generate_data (Data_info *specs);

double next_double ();

int next_uniform (long long min, long long max);

int next_gaussian (long long min, long long max);

int next_quadratic (long long min, long long max);

int next_bucket (long long min, long long max);

void print_array (Data *data);

void prettyprint_array (Data *data);

#endif
