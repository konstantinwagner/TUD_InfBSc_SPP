#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    // Check argument counter
    if (argc != 3) {
        printf("Invalid argument counter (got %i instead of 3 args)\n", argc);
        printf("Required format: <command> <amount> <chunksize>\n");
        return -1;
    }

    // Parse arguments
    int amount = atoi(argv[1]);
    int chunk_size = atoi(argv[2]);

    printf("Run algorithm with amount=%i numbers and dynamic chunk_size=%i\n", amount, chunk_size);

    // Start timer
    double needed_time = omp_get_wtime();

    bool *prim_array = malloc(sizeof(bool) * amount);

    // Init array with true
    #pragma omp parallel for schedule(dynamic, chunk_size)
    for (int i = 0; i < amount; i++)
        prim_array[i] = 1;

    // 0,1,2 are no prim numbers by definition
    prim_array[0] = 0;
    prim_array[1] = 0;
    prim_array[2] = 0;

    // Search for non-prim numbers and set them to 'false'
    double maxsearch = sqrt(amount);
    for (int i = 2; i < maxsearch; i++) {
        #pragma omp parallel for schedule(dynamic, chunk_size)
        for (int j = i * i; j < amount; j += i)
            prim_array[j] = 0;
    }

    // Stop timer
    needed_time = omp_get_wtime() - needed_time;

    // Print out found prim values
    for (int i = 0; i < amount; i++)
        if (prim_array[i] == 1) printf("%i\n", i);

    // Clean up
    free(prim_array);

    // Print out needed time
    printf("\nFinished after %f seconds!\n", needed_time);

    return 0;
}
