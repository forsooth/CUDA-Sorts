#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "structs.h"
#include "array_maker.h"
#include "insertion.h"
#include "mergeSort.h"

typedef long long Parses(const char *str, char **endptr, int base);
typedef unsigned long long Parseu(const char *str, char **endptr, int base);

long long parse_signed(char *arg, char *str, Parses *parseint);
unsigned long long parse_unsigned(char *arg, char *str, Parseu *parseuint);


/* Parse command line arguments, generate a random array to the client's 
 * specifications, and pass the array to the specified sorting algorithms */
int main (int argc, char *argv[])
{

        Data_info *specs = (Data_info *)malloc(sizeof(*specs));
        specs->sample_size = 10000;
        specs->max = 100000;
        specs->min = -10;

        Sort algorithm;
        Concurrency parallelism;

        /* ===========================================

                    Main loop though CL args

           =========================================== */
        for (int i = 1; i < argc; i++) {
                char *arg = argv[i];

                /* ========================================
                       -n, -num, and -number arguments 
                   ======================================== */
                if (strcmp(arg, "-n") == 0 || strcmp(arg, "-num") == 0
                                      || strcmp(arg, "-number") == 0) {
                      
                        if (i + 1 == argc) {
                                fprintf(stderr, "ERROR: command line argument "
                                                "%s was not followed by "
                                                "a value.\n", arg);
                                exit(EXIT_FAILURE);
                        }

                        i++;
                        char *num_str = argv[i];

                        unsigned long long num = 
                                       parse_unsigned(arg, num_str, &strtoull);

                        specs->sample_size = num;
                }

                /* ========================================
                    -d, -dist, and -distribution arguments 
                   ======================================== */
                else if (strcmp(arg, "-d") == 0 || strcmp(arg, "-dist") == 0
                                      || strcmp(arg, "-distribution") == 0) {
                      
                        if (i + 1 == argc) {
                                fprintf(stderr, "ERROR: command line argument "
                                                "%s was not followed by "
                                                "a value.\n", arg);
                                exit(EXIT_FAILURE);
                        }

                        i++;
                        char *dist_str = argv[i];

                        if (strcmp(dist_str, "gaussian") == 0 || 
                            strcmp(dist_str, "g") == 0) {
                                specs->dist = GAUSSIAN;

                        } else if (strcmp(dist_str, "uniform") == 0 || 
                                   strcmp(dist_str, "u") == 0) {
                                specs->dist = UNIFORM;

                        } else if (strcmp(dist_str, "constant") == 0 || 
                                   strcmp(dist_str, "c") == 0) {
                                specs->dist = CONSTANT;

                        } else if (strcmp(dist_str, "quadratic") == 0 || 
                                   strcmp(dist_str, "q") == 0) {
                                specs->dist = QUADRATIC;

                        } else if (strcmp(dist_str, "buckets") == 0 || 
                                   strcmp(dist_str, "b") == 0) {
                                specs->dist = BUCKETS;

                        } else {
                                fprintf(stderr, "ERROR: the distribution "
                                                "specified (%s) was not "
                                                "recognized.\n", dist_str);
                                exit(EXIT_FAILURE);
                        }
                      
                /* ========================================
                           -t and -type arguments 
                   ======================================== */  
                } else if (strcmp(arg, "-t") == 0 || 
                           strcmp(arg, "-type") == 0) {
                      
                        if (i + 1 == argc) {
                                fprintf(stderr, "ERROR: command line argument "
                                                "%s was not followed by "
                                                "a value.\n", arg);
                                exit(EXIT_FAILURE);
                        }

                        i++;
                        char *type_str = argv[i];

                        if (strcmp(type_str, "int") == 0 || 
                            strcmp(type_str, "i") == 0) {
                                specs->contents = INT;

                        } else if (strcmp(type_str, "fp") == 0 || 
                                   strcmp(type_str, "f") == 0 || 
                                   strcmp(type_str, "float") == 0 || 
                                   strcmp(type_str, "floating-point") == 0) {
                                specs->contents = FLOAT;
                        } else {
                                fprintf(stderr, "ERROR: the datatype "
                                                "specified (%s) was not "
                                                "recognized.\n", type_str);
                                exit(EXIT_FAILURE);
                        }

                /* ========================================
                          -r and -range arguments 
                   ======================================== */
                } else if (strcmp(arg, "-r") == 0 ||
                           strcmp(arg, "-range") == 0) {
                      
                        if (i + 2 == argc) {
                                fprintf(stderr, "ERROR: command line argument "
                                                "%s was not followed by "
                                                "enough values.\n", arg);
                                exit(EXIT_FAILURE);
                        }

                        i++;
                        char *min_str = argv[i];
                        i++;
                        char *max_str = argv[i];

                        long long min = parse_signed(arg, min_str, &strtoll);
                        long long max = parse_signed(arg, max_str, &strtoll);

                        specs->min = min;
                        specs->max = max;

                /* ========================================
                           -s and -sort arguments 
                   ======================================== */

                } else if (strcmp(arg, "-s") == 0 ||
                           strcmp(arg, "-sort") == 0) {
                      
                        if (i + 1 == argc) {
                                fprintf(stderr, "ERROR: command line argument "
                                                "%s was not followed by "
                                                "enough values.\n", arg);
                                exit(EXIT_FAILURE);
                        }

                        i++;
                        char *sort_name = argv[i];

                        if (strcmp(sort_name, "quick") == 0 ||
                            strcmp(sort_name, "quicksort") == 0) {
                                algorithm = QUICK;

                        } else if (strcmp(sort_name, "shell") == 0 ||
                            strcmp(sort_name, "shell-sort") == 0) {
                                algorithm = SHELL;

                        } else if (strcmp(sort_name, "merge") == 0||
                            strcmp(sort_name, "merge-sort") == 0) {
                                algorithm = MERGE;

                        } else if (strcmp(sort_name, "insertion") == 0 ||
                            strcmp(sort_name, "insertion-sort") == 0) {
                                algorithm = INSERTION;

                        } else if (strcmp(sort_name, "heap") == 0 ||
                            strcmp(sort_name, "heap-sort") == 0) {
                                algorithm = HEAP;

                        } else if (strcmp(sort_name, "radix") == 0 ||
                            strcmp(sort_name, "radix-sort") == 0) {
                                algorithm = RADIX;

                        } else if (strcmp(sort_name, "bitonic") == 0 ||
                            strcmp(sort_name, "bitonic-sort") == 0) {
                                algorithm = BITONIC;

                        } else {
                                fprintf(stderr, "No valid algorithm specified"
                                                " after %s", arg);
                                exit(EXIT_FAILURE);
                        }

                /* ========================================
                           -p and -parallel arguments 
                   ======================================== */

                } else if (strcmp(arg, "-p") == 0 ||
                           strcmp(arg, "-parallel") == 0) {
                      
                        if (i + 1 == argc) {
                                fprintf(stderr, "ERROR: command line argument "
                                                "%s was not followed by "
                                                "enough values.\n", arg);
                                exit(EXIT_FAILURE);
                        }

                        i++;
                        char *par = argv[i];

                        if (strcmp(par, "p") == 0 ||
                            strcmp(par, "parallel") == 0) {
                                parallelism = PARALLEL;

                        } else if (strcmp(par, "s") == 0 ||
                            strcmp(par, "serial") == 0) {
                                parallelism = SERIAL;

                        } else if (strcmp(par, "b") == 0 ||
                            strcmp(par, "both") == 0) {
                                parallelism = BOTH;

                        } else {
                                fprintf(stderr, "No valid parallelism "
                                                "specified after %s", arg);
                                exit(EXIT_FAILURE);
                        }

                 /* ========================================
                           -o and -order arguments 
                   ======================================== */

                } else if (strcmp(arg, "-o") == 0 ||
                           strcmp(arg, "-order") == 0) {
                      
                        if (i + 1 == argc) {
                                fprintf(stderr, "ERROR: command line argument "
                                                "%s was not followed by "
                                                "enough values.\n", arg);
                                exit(EXIT_FAILURE);
                        }

                        i++;
                        char *order = argv[i];
 
                        if (strcmp(order, "s") == 0 ||
                            strcmp(order, "sorted") == 0) {
              
                                specs->order = SORTED;

                        } else if (strcmp(order, "r") == 0 ||
                            strcmp(order, "reversed") == 0) {
                                specs->order = REVERSED;

                        } else if (strcmp(order, "n") == 0 ||
                            strcmp(order, "nearly-sorted") == 0) {
                                specs->order = NEARLYSORTED;

                        } else if (strcmp(order, "u") == 0 ||
                            strcmp(order, "unsorted") == 0 ||
                            strcmp(order, "random") == 0 ||
                            strcmp(order, "shuffled") == 0) {
                                specs->order = UNSORTED;

                        }else {
                                fprintf(stderr, "No valid array sortedness "
                                                "specified after %s", arg);
                                exit(EXIT_FAILURE);
                        }
                }

               
        }

        fprintf(stderr, "Parsed command-line arguments.\n\n");

        fprintf(stderr, "Will create & sort array with properties:\n");

        fprintf(stderr, "Length: %llu\n", specs->sample_size);

        if (specs->dist == UNIFORM) {
                fprintf(stderr, "Distribution: uniform\n");
        } else if (specs->dist == GAUSSIAN) {
                fprintf(stderr, "Distribution: gaussian\n");
        } else if (specs->dist == CONSTANT) {
                fprintf(stderr, "Distribution: constant\n");
        } else if (specs->dist == QUADRATIC) {
                 fprintf(stderr, "Distribution: quadratic\n");
        } else if (specs->dist == BUCKETS) {
                fprintf(stderr, "Distribution: buckets\n");
        }

        if (specs->contents == INT) {
                fprintf(stderr, "Elements of type: int\n");
        } else if (specs->contents == FLOAT) {
                fprintf(stderr, "Elements of type: float\n");
        }

        fprintf(stderr, "Minimum element: %lld\n", specs->min);
        fprintf(stderr, "Maximum element: %lld\n", specs->max);

        if (specs->order == SORTED) {
                fprintf(stderr, "Sortedness: sorted\n\n");
        } else if (specs->order == REVERSED) {
                fprintf(stderr, "Sortedness: reversed\n\n");
        } else if (specs->order == NEARLYSORTED) {
                fprintf(stderr, "Sortedness: nearly sorted\n\n");
        } else if (specs->order == UNSORTED) {
                fprintf(stderr, "Sortedness: random\n\n");
        } 

        if (algorithm == ALL) {
                fprintf(stderr, "With all algorithms\n");
        } else if (algorithm == BITONIC) {
                fprintf(stderr, "With algorithm: bitonic sort\n");
        } else if (algorithm == RADIX) {
                fprintf(stderr, "With algorithm: radix sort\n");
        } else if (algorithm == QUICK) {
                fprintf(stderr, "With algorithm: quicksort\n");
        } else if (algorithm == MERGE) {
                fprintf(stderr, "With algorithm: merge sort\n");
        } else if (algorithm == SHELL) {
                fprintf(stderr, "With algorithm: shellsort\n");
        } else if (algorithm == HEAP) {
                fprintf(stderr, "With algorithm: heap sort\n");
        } else if (algorithm == INSERTION) {
                fprintf(stderr, "With algorithm: insertion sort\n");
        } 

        if (parallelism == BOTH) {
                fprintf(stderr, "Running both in serial "
                                "and parallel\n\n");
        } else if (parallelism == SERIAL) {
                fprintf(stderr, "Running in serial\n\n");
        } else if (parallelism == PARALLEL) {
                fprintf(stderr, "Running in parallel\n\n");
        }

        srand(time(NULL));
        Data *data = generate_data(specs);
        print_array(data, specs);
        if (algorithm == ALL) {
                fprintf(stderr, "With all algorithms, to be done\n");
        } else if (algorithm == BITONIC) {
                fprintf(stderr, "With algorithm: bitonic sort to be done\n");
        } else if (algorithm == RADIX) {
                fprintf(stderr, "With algorithm: radix sort to be done\n");
        } else if (algorithm == QUICK) {
                fprintf(stderr, "With algorithm: quicksort to be done\n");
        } else if (algorithm == MERGE) {
                fprintf(stderr, "Invoking algorithm: merge sort\n");
                mergeSort(data);
        } else if (algorithm == SHELL) {
                fprintf(stderr, "With algorithm: shellsort to be done\n");
        } else if (algorithm == HEAP) {
                fprintf(stderr, "With algorithm: heap sort to be done\n");
        } else if (algorithm == INSERTION) {
                fprintf(stderr, "Invoking algorithm: insertion sort\n");
                insertion(data);
        } 


}

long long parse_signed(char *arg, char *str, Parses *parseint) {
        
        int digits = strlen(str);

        if (digits <= 0) {
                fprintf(stderr, "ERROR: Impossibly, an arg"
                               " was an empty string.\n");
                exit(EXIT_FAILURE);

        }

        long long num = parseint(str, NULL, 0);

        if (errno == ERANGE || errno == EINVAL) {
                fprintf(stderr, "ERROR: command line argument"
                                " %s was not followed by a "
                                "valid value. Value provided "
                                "was: %s.\n", arg, str);
                exit(EXIT_FAILURE);
        } else if (num == 0 && digits != 1 && str[0] == '0') {
                fprintf(stderr, "ERROR: the value following "
                                "argument %s was not able to "
                                "be interpreted as an integer."
                                " Value was: %s\n", arg, 
                                str);
                exit(EXIT_FAILURE);
        }

        return num;
}

unsigned long long parse_unsigned(char *arg, char *str, Parseu *parseuint) {
        
        int digits = strlen(str);

        if (digits <= 0) {
                fprintf(stderr, "ERROR: Impossibly, an arg"
                               " was an empty string.\n");
                exit(EXIT_FAILURE);

        } else if (str[0] == '-') {
                fprintf(stderr, "ERROR: value passed to argument %s cannot "
                                "be a negative number. Value "
                                "was %s.\n", arg, str);
                exit(EXIT_FAILURE);
        }

        unsigned long long num = 
                        parseuint(str, NULL, 0);

        if (errno == ERANGE || errno == EINVAL) {
                fprintf(stderr, "ERROR: command line argument"
                                " %s was not followed by a "
                                "valid value. Value provided "
                                "was: %s.\n", arg, str);
                exit(EXIT_FAILURE);
        } else if (num == 0 && digits != 1 && str[0] == '0') {
                fprintf(stderr, "ERROR: the value following "
                                "argument %s was not able to "
                                "be interpreted as an integer."
                                " Value was: %s\n", arg, 
                                str);
                exit(EXIT_FAILURE);
        }

        return num;
}
