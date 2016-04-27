#!/bin/bash
echo "Compiling executable ./a.out";
nvcc -g -DSILENT -I/usr/local/cuda-7.5/ *.cu;
echo "Beginning data collection";
echo "BEGIN" > testoutput.txt;
for i in {0..100000000..1000000};
do echo "n is $i";
foo=$(($i/1000000));
echo "$foo% done";
echo "n is: $i" >> testoutput.txt;
./a.out -n $i -p b -s radix >> testoutput.txt;
done;
echo "END" >> testoutput.txt;
echo "Finished collecting data";
