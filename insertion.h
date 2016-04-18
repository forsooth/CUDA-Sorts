#ifndef INSERTION_H
#define INSERTION_H

#include "structs.h"
#include "checkSortedness.h"

void insertion(Data_info *info, Data *data) {
    
    if (info->contents == INT) {
    
        for (int i = 1; i < info->sample_size; i++) {
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
    
    } else if (info->contents == FLOAT) {
    
        for (int i = 1; i < info->sample_size; i++) {
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
    checkSortedness(info, data);
};

#endif
