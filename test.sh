#!/bin/bash
echo "Compiling executable ./a.out";
nvcc -g -DSILENT -I/usr/local/cuda-7.5/ *.cu;
echo "Beginning data collection";
echo "BEGIN" > test2output.txt;
for i in {10..1000000..100000};
do echo "n is $i";
foo=$(($i/10000));
echo "$foo% done";
echo "n is: $i" >> test2output.txt;
./a.out -n $i -p b >> test2output.txt;
done;
echo "END" >> test2output.txt;
echo "Finished collecting data";
