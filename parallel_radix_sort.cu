
#include "parallel_radix_sort.h"

void parallel_radix_sort(Data *data) {

        if (data->array_used == INT) {
                parallel_radix_sort_int(data);
        } else if (data->array_used == FLOAT) {
                parallel_radix_sort_float(data);
        }

};

void parallel_radix_sort_int(Data *data)
{

        clock_t begin, end;
        double time_spent;

        int *a = data->intarray;
        thrust::host_vector<int> h_a;
        thrust::device_vector<int> d_a;

        for (int i = 0; i < data->length; i++) {
                h_a.push_back(a[i]);
        }

        begin = clock();

        d_a = h_a;
        thrust::sort(d_a.begin(), d_a.end());
        h_a = d_a;

        end = clock();

        for (int i = 0; i < data-> length; i++) {
                a[i] = h_a[i];
        }

        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        fprintf(stdout, "Parallel Radix time: %f\n", time_spent);

}

void parallel_radix_sort_float(Data *data)
{

}

