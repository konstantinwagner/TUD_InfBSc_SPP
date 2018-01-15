#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdint.h>


/**
 * Initializes matrix mat.
 */
void init_mat(double *mat, uint64_t q, int coords[2], int dim) {
    uint64_t n = dim * q;

    for (uint64_t i_local = 0; i_local < q; i_local++) {
        for (uint64_t j_local = 0; j_local < q; j_local++) {
            uint64_t i = i_local + coords[0] * q;
            uint64_t j = j_local + coords[1] * q;

            mat[i_local * q + j_local] = i * n + j;
        }
    }
}


/**
 * Cache-friendly (fast) variant of matrix multiplication. 
 * Multiplies a_mat by b_mat and stores the result in c_mat.
 * This function can be used for multiplying parts of matrices 
 * and for verifying the results in the end.
 */
void mult_mat_fast(double *a_mat, double *b_mat, double *c_mat,
                   uint64_t c_rows, uint64_t c_cols, uint64_t a_cols) {
    for (uint64_t k = 0; k < a_cols; ++k) {
        for (uint64_t i = 0; i < c_rows; ++i) {
            double r = a_mat[i * a_cols + k];
            for (uint64_t j = 0; j < c_cols; ++j) {
                c_mat[i * c_cols + j] += r * b_mat[k * c_cols + j];
            }
        }
    }
}


/**
 * This function verifies the result for the local block.
 * Returns 1 if multiplication is correct, and 0 otherwise.
 */
int verify_results(double *mat, uint64_t q, int coords[2], int dim) {
    uint64_t n = q * dim;
    double result_local = 0, result_expected = 0;

    uint64_t gaussian_k_sum = (((n - 1) * (n - 1) + (n - 1)) / 2);
    uint64_t gaussian_k2_sum = (uint64_t) ((2 * pow((n - 1), 3) + 3 * pow((n - 1), 2) + (n - 1)) / 6);

    for (uint64_t i_local = 0; i_local < q; i_local++) {
        for (uint64_t j_local = 0; j_local < q; j_local++) {
            uint64_t i = i_local + coords[0] * q;
            uint64_t j = j_local + coords[1] * q;

            result_local += mat[i_local * q + j_local];
            result_expected +=
                    (i * (n * n) * gaussian_k_sum) + (i * j * (n * n)) + (n * gaussian_k2_sum) + (j * gaussian_k_sum);
        }
    }

    return (result_expected == result_local) ? 1 : 0;
}


int main(int argc, char **argv) {

    int world_rank, cart_rank, world_size;
    double *a_mat = NULL;
    double *b_mat = NULL;
    double *c_mat = NULL;
    MPI_Comm comm_cart = MPI_COMM_NULL;

    /* Initialize and get initial info */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (argc < 2) {
        if (world_rank == 0) {
            printf("Usage: %s <block size>\n", argv[0]);
        }
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    /* Block size */
    uint64_t q = atoll(argv[1]);

    /* Create a cartesian communicator (subtask 2.1) */
    int p = world_size;
    int p_sqrt = (int) sqrt(p);

    const int dims[] = {p_sqrt, p_sqrt};
    const int periods[] = {1, 1};

    /* Initialize */
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 1, &comm_cart);
    MPI_Comm_rank(comm_cart, &cart_rank);

    /* Initialize local blocks of A, B, and C (subtask 2.2) */
    int coords[] = {0, 0};
    uint64_t blocksize = q * q;

    a_mat = malloc(blocksize * sizeof(double));
    b_mat = malloc(blocksize * sizeof(double));
    c_mat = malloc(blocksize * sizeof(double));

    init_mat(a_mat, q, coords, p_sqrt);
    init_mat(b_mat, q, coords, p_sqrt);

    /* Initial skewing of the blocks  (subtask 2.3) */
    int a_src, a_dest_rcv, a_dest_snd;
    int b_src, b_dest_rcv, b_dest_snd;

    // Fetch shifting partners for matrix A
    MPI_Cart_shift(comm_cart, 0, coords[1], &a_src, &a_dest_rcv);
    MPI_Cart_shift(comm_cart, 0, -coords[1], &a_src, &a_dest_snd);

    // Fetch shifting partners for matrix B
    MPI_Cart_shift(comm_cart, 1, coords[1], &b_src, &b_dest_rcv);
    MPI_Cart_shift(comm_cart, 1, -coords[1], &b_src, &b_dest_snd);

    MPI_Status a_status;
    MPI_Sendrecv_replace(a_mat, (int) blocksize, MPI_DOUBLE, a_dest_snd, 0, a_dest_rcv, 0, comm_cart, &a_status);

    MPI_Status b_status;
    MPI_Sendrecv_replace(b_mat, (int) blocksize, MPI_DOUBLE, b_dest_snd, 0, b_dest_rcv, 0, comm_cart, &b_status);

    mult_mat_fast(b_mat, a_mat, c_mat, q, q, q);

    /* Main iteration (subtask 2.6) */
    for (uint64_t i = 0; i < p_sqrt - 1; i++) {
        /* Shift matrices A and B (subtask 2.4) */
        // Shift matrix A leftwards
        MPI_Cart_shift(comm_cart, 0, 1, &a_src, &a_dest_rcv);
        MPI_Cart_shift(comm_cart, 0, -1, &a_src, &a_dest_snd);

        // Shift matrix B upwards
        MPI_Cart_shift(comm_cart, 1, 1, &b_src, &b_src);
        MPI_Cart_shift(comm_cart, 1, -1, &b_src, &b_dest_snd);

        // Send matrix a
        MPI_Status a_status_shift;
        MPI_Sendrecv_replace(a_mat, blocksize, MPI_DOUBLE, a_dest_snd, 0, a_dest_rcv, 0, comm_cart, &a_status_shift);

        // Send matrix b
        MPI_Status b_status_shift;
        MPI_Sendrecv_replace(b_mat, blocksize, MPI_DOUBLE, b_dest_snd, 0, b_dest_rcv, 0, comm_cart, &b_status_shift);

        /* Perform local matrix multiply on initial data (subtask 2.5) */
        // Multiply matrix
        mult_mat_fast(b_mat, a_mat, c_mat, q, q, q);
    }

    /* Verify the results (subtask 2.7) */
    int success = verify_results(c_mat, q, coords, p_sqrt);

    int global_result = 0;
    MPI_Reduce(&success, &global_result, 1, MPI_INT, MPI_SUM, 0, comm_cart);

    if (world_rank == 0) {
        printf("Correct: %d\n", global_result);
    }


    MPI_Finalize();

    return 0;
}
