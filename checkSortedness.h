#ifndef CHECKSORTEDNESS_H
#define CHECKSORTEDNESS_H

#include "structs.h"
#include <stdio.h>

void checkSortedness(Data_info *info, Data *data) {

    if (info->contents == INT) {
    
        for (int i = 1; i < info->sample_size; i++) {
            if (data->intarray[i] < data->intarray[i - 1]) {
                fprintf(stderr, "Not sorted at %d is %d, at %d is %d.\n", 
                        i - 1, data->intarray[i - 1], i, data->intarray[i]);
                return;
            }
                
        }
    
    } else if (info->contents == FLOAT) {
    
        for (int i = 1; i < info->sample_size; i++) {
            if (data->floatarray[i] < data->floatarray[i - 1]) {
                fprintf(stderr, "Not sorted at %d is %lf, at %d is %lf.\n", 
                        i - 1, data->floatarray[i - 1], i, data->floatarray[i]);
                return;
             }
        }
  
      
    }

    fprintf(stderr, "Sorted.\n");


};

#endif
