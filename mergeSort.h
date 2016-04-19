#ifndef MERGE_H
#define MERGE_H
#include "structs.h"
#include "checkSortedness.h"
void mergeSort_int(int *arr, int leftIndex, int rightIndex);
void mergeSort_float(float *arr, int leftIndex, int rightIndex);
void mergeSort(Data *data) {
    
    if (data->array_used == INT) {
        
        mergeSort_int(data->intarray, 0, data->length - 1);
    } else if (data->array_used == FLOAT) {
    
        mergeSort_float(data->floatarray, 0, data->length - 1);
    }
    checkSortedness(data);
};

void mergeSort_int(int *arr, int leftIndex, int rightIndex) {

    if (leftIndex >= rightIndex)
        return;
        
    int middle = (leftIndex + rightIndex) / 2;
    //divide
    mergeSort_int(arr, leftIndex, middle);
    mergeSort_int(arr, middle + 1, rightIndex);
    
    //merge
    int length = (rightIndex - leftIndex + 1);
    int *tmp = (int *)malloc(length * sizeof(int));
    
    int lhalf = leftIndex;
    int rhalf = middle + 1;
    int tmpIndex = 0;
    
    while (lhalf <= middle && rhalf <= rightIndex) {
        tmp[tmpIndex++] = arr[lhalf] < arr[rhalf] ? arr[lhalf++] : arr[rhalf++];
    }
    
    while (lhalf <= middle) {
        tmp[tmpIndex++] = arr[lhalf++];
    }
    
    while (rhalf <= rightIndex) {
    
        tmp[tmpIndex++] = arr[rhalf++];
    }
    
    tmpIndex = 0;
    lhalf = leftIndex;
    //copy back
    while (lhalf <= rightIndex) {
        arr[lhalf++] = tmp[tmpIndex++];
    }
    
    return; 
    

}

void mergeSort_float(float *arr, int leftIndex, int rightIndex) {

    if (leftIndex >= rightIndex)
        return;
        
    int middle = (leftIndex + rightIndex) / 2;
    //divide
    mergeSort_float(arr, leftIndex, middle);
    mergeSort_float(arr, middle + 1, rightIndex);
    
    //merge
    int length = (rightIndex - leftIndex + 1);
    float *tmp = (float *)malloc(length * sizeof(float));
    
    int lhalf = leftIndex;
    int rhalf = middle + 1;
    int tmpIndex = 0;
    
    while (lhalf <= middle && rhalf <= rightIndex) {
        tmp[tmpIndex++] = arr[lhalf] < arr[rhalf] ? arr[lhalf++] : arr[rhalf++];
    }
    
    while (lhalf <= middle) {
        tmp[tmpIndex++] = arr[lhalf++];
    }
    
    while (rhalf <= rightIndex) {
    
        tmp[tmpIndex++] = arr[rhalf++];
    }
    
    tmpIndex = 0;
    lhalf = leftIndex;
    //copy back
    while (lhalf <= rightIndex) {
        arr[lhalf++] = tmp[tmpIndex++];
    }
    
    return; 

}

#endif
