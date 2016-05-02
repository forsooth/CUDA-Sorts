#!/bin/bash
echo "Compiling executable ./a.out";
nvcc -g -DSILENT -I/usr/local/cuda-7.5/ *.cu;
echo "Beginning data collection";
echo "BEGIN" > test2output.txt;
for i in {10..100000..10000};
do echo "n is $i";
foo=$(($i/10000));
echo "$foo% done";
echo "n is: $i" >> test2output.txt;
./a.out -n $i -s shell -p s >> test2output.txt;
./a.out -n $i -s merge -p s >> test2output.txt;
./a.out -n $i -s insertion -p s >> test2output.txt;
./a.out -n $i -s radix -p s >> test2output.txt;
./a.out -n $i -s radix -p p >> test2output.txt;
done;
echo "END" >> test2output.txt;
echo "Finished collecting data";
