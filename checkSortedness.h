#ifndef CHECKSORTEDNESS_H
#define CHECKSORTEDNESS_H

#include "structs.h"
#include <stdio.h>

void checkSortedness(Data *data) {

    if (data->array_used == INT) {
    
        for (int i = 1; i < data->length; i++) {
            if (data->intarray[i] < data->intarray[i - 1]) {
                printf("Not sorted at %lld is %lld, at %lld is %lld.\n", 
                        i - 1, data->intarray[i - 1], i, data->intarray[i]);
                return;
            }
                
        }
    
    } else if (data->array_used == FLOAT) {
    
        for (int i = 1; i < data->length; i++) {
            if (data->floatarray[i] < data->floatarray[i - 1]) {
                printf("Not sorted at %lld is %lf, at %lld is %lf.\n", 
                        i - 1, data->floatarray[i - 1], i, data->floatarray[i]);
                return;
             }
        }
  
      
    }

    printf("Sorted.\n");


};

#endif
