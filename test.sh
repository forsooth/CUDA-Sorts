#!/bin/bash
 
for i in {10..10000};
do  
 
 
./a.out -n $i -s bitonic -p p >> test1.txt;
done;
 
