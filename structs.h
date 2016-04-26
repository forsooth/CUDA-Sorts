#ifndef STRUCTS
#define STRUCTS

/* Used to determine which sort to use */
typedef enum {ALL, BITONIC, RADIX, QUICK, MERGE, SHELL, HEAP, INSERTION} Sort;
/* Used to determine which version of the algorithms specified to use */
typedef enum {BOTH, SERIAL, PARALLEL}  Concurrency;

/* Used in generating a random distribution */
typedef enum {UNIFORM, GAUSSIAN, CONSTANT, QUADRATIC, BUCKETS} Data_dist;
typedef enum {UNSORTED, SORTED, REVERSED, NEARLYSORTED} Sortedness;
typedef enum {INT, FLOAT} Data_type;

/* Data specified in command line arguments pertaining to the
 * data to generate */
typedef struct Data_info {
        Data_dist dist;
        Data_type contents;
        Sortedness order;
        long long min;
        long long max;
        unsigned long long sample_size;
} Data_info;

typedef struct Data {
        unsigned int length;
        int array_used;
        int *intarray;
        float *floatarray;
} Data;

typedef struct Grid {
    int blockx;
    int blocky;
    int blockz;
} Grid;

#endif
