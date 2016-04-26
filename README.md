# CUDA-Sorts
Our final project for COMP-140/EE-194: an analysis of sorting algorithms in serial and parallel

##Summary:
The recommended debugging command is:

`./a.out -n 10 -r 0 100 -s merge -p s`

Which will sort 10 integers from 0 to 100. Replace 'merge' with your algorithm, and '-p s' with '-p p' if you want to test a parallel algorithm.

##Command Line Arguments:
* The `-n`, `-num`, or `-number` argument specifies how many numbers to sort.
* The `-d`, `-dist`, or `-distribution` argument specifies which distribution to use for the numbers, for example making the data out of only ten numbers, gaussian distributed numbers, etc. The default is to just use uniformly distrubited random numbers.
* The `-t` or `-type` argument specifies what type of data to sort, floats or integers.
* The `-r` or `-range` argument specifies the minimum and maximum element that the user wants to appear in their list.
* The `-s` or `-sort` argument specifies which sorting algorithm to use.
* The `-p` or `-parallel` argunt specifies whether to sort in serial or in parallel.
* The `-o` or `-order` argument specifies how sorted the array is supposed to be: for example, unsorted, nearly sorted, reversed, etc.


####Options for `-n`
This argument is followed by one non-negative integer.

####Options for `-d`
This argument is followed by one of the following strings: gaussian, g, uniform, u, constant, c, quadratic, q, buckets, b.

####Options for `-t`
This argument is followed by one of the following strings: int, i, fp, f, float, floating-point.

####Options for `-r`
This argument is followed by two integers, the second larger than the first, separated by whitespace. Negative values are allowed.

####Options for `-s`
This argument is followed by one of the following strings: quick, quicksort, shell, shell-sort, merge, merge-sort, insertion, insertion-sort, heap, heap-sort, radix, radix-sort, bitonic, bitonic-sort.

####Options for `-p`
This argument is followed by one of the following strings: p, parallel, s, serial, b, both.

####Options for `-o`
This argument is followed by one of the following strings: s, sorted, r, reversed, n, nearly-sorted, u, unsorted, random, shuffled.
Note that these are not yet implemented.

##Defaults
By default the program will attempt to sort 10000 uniformly random unsorted integers ranging from -10 to 100000 using all algorithms and in all
parallelisms.

##Example usage:
./cuda-sorts -n 1000 -d gaussian -r 0 123456 -s quicksort
Will attempt to sort 1000 unsorted uniformly random integers in a gaussian distribution ranging from 0 to 123456 with the quicksort algorithm in both serial and parallel.
