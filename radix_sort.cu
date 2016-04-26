#include "radix_sort.h"
#define BITS 4

void radix_sort(Data *data) {

    if (data->array_used == INT) {
        radix_sort_int(data);
    } else if (data->array_used == FLOAT) {
        radix_sort_float(data);
    }

};

long long find_max_int (Data *data) {
        unsigned long long length = data->length;
        int *a = data->intarray;
        long long max = a[0];

        for (unsigned long long i = 1; i < length; i++) {
                if (a[i] > max) {
                        max = a[i];
                }
        }

        return max;


}

void radix_sort_int(Data *data) {

        long long max = find_max_int(data);
        unsigned long long length = data->length;
        int *a = data->intarray;

        int b[length];

        int buckets = 1 << BITS;
        int mask = buckets - 1;

        int pos = 0;

        while (max >> (pos * BITS) > 0) {
                int bucket[1 << BITS] = {0};

                for (int i = 0; i < length; i++) {
                        bucket[(a[i] >> (pos * BITS)) & mask]++;
                }

                for (int i = 1; i < buckets; i++) {
                        bucket[i] += bucket [i - 1];
                }

                for (int i = length - 1; i >= 0; i--) {
                        b[--bucket[(a[i] >> (pos * BITS)) & mask]] = a[i];
                }

                for (int i = 0; i < length; i++) {
                        a[i] = b[i];
                }

                pos++;
        }


}

void radix_sort_float(Data *data) {



}
