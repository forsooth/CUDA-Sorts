#include "check_sorted.h"

void check_sorted(Data *data) {

    if (data->array_used == INT) {

        for (int i = 1; i < data->length; i++) {
            if (data->intarray[i] < data->intarray[i - 1]) {
                fprintf(stderr, "Not sorted at %d is %d, at %d is %d.\n",
                        i - 1, data->intarray[i - 1], i, data->intarray[i]);
                return;
            }
        }
    } else if (data->array_used == FLOAT) {

        for (int i = 1; i < data->length; i++) {
            if (data->floatarray[i] < data->floatarray[i - 1]) {
                fprintf(stderr, "Not sorted at %d is %lf, at %d is %lf.\n",
                        i - 1, data->floatarray[i - 1], i, data->floatarray[i]);
                return;
             }
        }
    }

    printf("Sorted.\n");


};
