#include "radix_sort.h"
#ifndef BITS
#define BITS 9
#endif

void radix_sort(Data *data) {

    if (data->array_used == INT) {
        radix_sort_int(data);
    } else if (data->array_used == FLOAT) {
        radix_sort_float(data);
    }

};

long long *find_max_int (Data *data) {
        unsigned long long length = data->length;
        int *a = data->intarray;
        long long max = a[0];
        long long min = a[0];

        for (unsigned long long i = 1; i < length; i++) {
                if (abs(a[i]) > max) {
                        max = abs(a[i]);
                }
                if (a[i] < min) {
                        min = a[i];
                }
        }

        long long *maxmin = (long long *) malloc(2 * sizeof(*maxmin));
        maxmin[0] = max;
        maxmin[1] = min;

        return maxmin;
}

void radix_sort_int(Data *data) {

        long long *maxmin = find_max_int(data);
        long long max = maxmin[0];
        long long min = maxmin[1];
        free(maxmin);
        unsigned long long length = data->length;
        int *a = data->intarray;

        int *b = (int *) malloc(length * sizeof(*b));

        int buckets = 1 << BITS;
        int mask = buckets - 1;

        int pos = 0;

        while (max >> (pos * BITS) > 0) {
                int bucket[1 << BITS] = {0};

                for (int i = 0; i < length; i++) {
                        bucket[(a[i] >> (pos * BITS)) & mask]++;
                }

                for (int i = 1; i < buckets; i++) {
                        bucket[i] += bucket[i - 1];
                }

                for (int i = length - 1; i >= 0; i--) {
                        b[--bucket[(a[i] >> (pos * BITS)) & mask]] = a[i];
                }

                for (int i = 0; i < length; i++) {
                        a[i] = b[i];
                }

                pos++;
        }

        if (min < 0) {

                int bucket[2] = {0};

                for (int i = 0; i < length; i++) {
                        bucket[(a[i] < 0)]++;
                }

                bucket[0] += bucket[1];

                for (int i = length - 1; i >= 0; i--) {
                        b[--bucket[(a[i] < 0)]] = a[i];
                }

                for (int i = 0; i < length; i++) {
                        a[i] = b[i];
                }
        }

        free(b);


}

void radix_sort_float(Data *data) {



}
