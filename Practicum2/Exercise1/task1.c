#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include "timing.h"

#define MAIN_THREAD 0

/**
 * Initializes matrix mat, such that each element equals to its
 * index. This function is for convenience, it is not required
 * to use it.
 */
void init_mat( double* mat, uint64_t rows, uint64_t cols ) {

    for( uint64_t i = 0; i < rows; ++i ) {
        for( uint64_t j = 0; j < cols; ++j ) {
            mat[i*cols + j] = i*cols + j;
        }
    }
}


/**
 * Cache-friendly (fast) variant of matrix multiplication.
 * Multiplies a_mat by b_mat and stores the result in c_mat.
 * This function can be used for multiplying parts of matrices
 * and for verifying the results in the end.
 */
void mult_mat_fast( double* a_mat, double* b_mat, double* c_mat,
                    uint64_t c_rows, uint64_t c_cols,
                    uint64_t a_cols ) {

    for( uint64_t k = 0; k < a_cols; ++k ) {
        for( uint64_t i = 0; i < c_rows; ++i ) {
            double r = a_mat[i*a_cols + k];
            for( uint64_t j = 0; j < c_cols; ++j ) {
                c_mat[i*c_cols + j] += r * b_mat[k*c_cols + j];
            }
        }
    }
}


/**
 * This function verifies the result.
 * Returns 1 if multiplication is correct, and 0 otherwise.
 */
int verify_results( double* mat, uint64_t n ) { //TODO Abändern
    uint64_t nn = n*n;
    double *tmp = malloc(nn * sizeof(double));
    double *out = malloc(nn * sizeof(double));
    init_mat(tmp, n, n);
    mult_mat_fast(tmp, tmp, out,
                  n, n, n);
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (out[n*i + j]!= mat[n*i + j]) {
                printf("Expected %f, but got %f in row %i, col %i.\n",
                       out[n*i+j], mat[n*i+j], i, j);
                free(tmp);
                free(out);
                return 0;
            }
        }
    }
    free(tmp);
    free(out);
    return 1;
}


int main( int argc, char** argv ) {

    int myrank, nprocs;
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
    MPI_Comm_size( MPI_COMM_WORLD, &nprocs );

    if( argc < 2 ) {
        printf( "Usage: %s <n>\n", argv[0] );
        exit( 1 );
    }

    uint64_t n = atoll( argv[1] );

    init_clock_time();

    /* Initialize */
    double *a;
    double *b;
    uint64_t len = n*n;

    b = calloc(len, sizeof(double));

    if (myrank == 0) {
        a = calloc(len, sizeof(double));
        init_mat(a, n, n);
        init_mat(b, n, n);
    }

    /* Take timestamp only after all the initialization steps are over */
    double start = get_clock_time();

    /* Distribute */

    MPI_Bcast(b, len, MPI_DOUBLE, MAIN_THREAD, MPI_COMM_WORLD);
    int rows = n/nprocs;
    int elements = n*rows;
    double *scattered_a = calloc(elements, sizeof(double));
    MPI_Scatter(a, elements, MPI_DOUBLE, scattered_a, elements, MPI_DOUBLE, MAIN_THREAD, MPI_COMM_WORLD);

    /* Multiply */
    double *scattered_c = calloc(elements, sizeof(double));
    mult_mat_fast(scattered_a, b, scattered_c, rows, n, n);
    free(scattered_a);

    /* Collect */
    MPI_Gather(scattered_c, elements, MPI_DOUBLE, b, elements, MPI_DOUBLE, MAIN_THREAD, MPI_COMM_WORLD);
    free(scattered_c);

    /* Take timestamp only after the collection/gathering step is over */
    double elapsed = get_clock_time() - start;

    /* Verify */
    if(myrank == MAIN_THREAD){
        if(verify_results(b, n) == 1){
            printf("Korrekt ausgeführt!\n");
        } else {
            printf("Fehlerhaft ausgeführt!\n");
        }
        free(a);
    }
    free(b);

    /* Get timing - max across all ranks */
    double elapsed_global;
    MPI_Reduce( &elapsed, &elapsed_global, 1, MPI_DOUBLE,
                MPI_MAX, MAIN_THREAD, MPI_COMM_WORLD );

    if( myrank == MAIN_THREAD ) {
        printf( "Elapsed time (ms): %f\n", elapsed_global );
    }

    MPI_Finalize();

    return 0;
}