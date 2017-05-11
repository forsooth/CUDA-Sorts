#include "shellsort.h"


void shellsort(Data *data) {

        if (data->array_used == INT) {
                shellsort_int(data);
        } else if (data->array_used == FLOAT) {
                shellsort_float(data);
        }

};

unsigned long long *generate_gaps(unsigned long long length) {

        int num_gaps = log(length) / log(2.48);

        unsigned long long *gaps = (unsigned long long *) malloc((num_gaps + 1) * sizeof(*gaps));

        for (int i = 0; i <= num_gaps; i++) {
                gaps[i] = pow(2.48, i);
                #ifdef PRINTGAPS
                fprintf(stderr, "%llu, ", gaps[i]);
                #endif
        }
        #ifdef PRINTGAPS
        fprintf(stderr, "\n");
        #endif

        return gaps;
}


void shellsort_int(Data *data) {
	clock_t begin, end;
        double time_spent;
        begin = clock();

        int* a = data->intarray;
        unsigned long long length = data->length;

        unsigned long long *gaps = generate_gaps(length);
        int num_gaps = sizeof(gaps) / sizeof(gaps[0]);

        int gapi = num_gaps;
        unsigned long long gap;
        int temp, j, i;

        while (gapi >= 0) {
                gap = gaps[gapi];
                for (i = gap; i < length; i++) {
                        temp = a[i];
                        for (j = i; (j >= gap) && (a[j - gap] > temp); j -= gap) {
                                a[j] = a[j - gap];
                        }

                        a[j] = temp;
                }

                gapi--;
        }

        free(gaps);

	end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        fprintf(stdout, "Serial Shellsort time: %f\n", time_spent);


}

void shellsort_float(Data *data) {



}

