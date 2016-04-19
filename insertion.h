#ifndef INSERTION_H
#define INSERTION_H

#include "structs.h"
#include "checkSortedness.h"

void insertion(Data *data) {
    
    if (data->array_used == INT) {
   
        for (int i = 1; i < data->length; i++) {
            for (int j = i; j > 0; j--) {
                if (data->intarray[j] < data->intarray[j - 1]) {
                    int tmp = data->intarray[j- 1];
                    data->intarray[j - 1] = data->intarray[j];
                    data->intarray[j] = tmp;
                } else {
                    break;
                }
            }
        }
    
    } else if (data->array_used == FLOAT) {
    
        for (int i = 1; i < data->length; i++) {
            for (int j = i; j > 0; j--) {
                if (data->floatarray[j] < data->floatarray[j - 1]) {
                    float tmp = data->floatarray[j- 1];
                    data->floatarray[j - 1] = data->floatarray[j];
                    data->floatarray[j] = tmp;
                } else {
                    break;
                }
            }
        }    
      
    }
    checkSortedness(data);
};

#endif
