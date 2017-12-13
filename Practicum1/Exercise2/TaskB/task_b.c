#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>

// Pre-declare used functions
bool check_sorted_sequence(int *array, int length);
void merge_sort(int *array, int *help, unsigned length);
void merge_sort_sort(int *array, int *help, unsigned left_array_length, unsigned right_array_length);

int main(int argc, char **argv) {
    // Check if argument counter matches conditions
    if (argc != 2) {
        printf("[ERROR] Got %i instead of 2 arguments\n", argc);
        printf("Required format: <command> <array_length>\n");
        return -1;
    }

    // Try to parse array length. Throw another error if an invalid length was returned.
    unsigned array_length = (unsigned) atoi(argv[1]);
    if (array_length < 0) {
        printf("[ERROR] Parsing array length argument returned negative value ('%s' -> '%i')\n", argv[1], array_length);
        return -1;
    }

    printf("Running sort algorithm with %i random values...\n", array_length);

    // Allocate main array with type 'int' and given length
    int *array = malloc(sizeof(int) * array_length);

    // Set time seed for rand()
    srand(omp_get_wtime());

    // Set random number to every array element
    for (int i = 0; i < array_length; i++) {
        array[i] = rand();
    }

    // Starting timer (includes: helper allocation & algorithm run)
    double needed_time = omp_get_wtime();

    // Allocate helper here to be included in the measured part
    int *help = malloc(sizeof(int) * array_length);

    // Execute merge-sort algorithm
    #pragma omp parallel
    #pragma omp single
    merge_sort(array, help, array_length);

    // Determinate if sorting was successful. Give user feedback afterwards.
    bool success = check_sorted_sequence(array, array_length);
    needed_time = omp_get_wtime() - needed_time;
    printf("Finished after %f seconds! Success: %s\n", needed_time, success ? "Yes" : "No");

    // Clean up
    free(array);
    free(help);

    // :)
    return 0;
}


/**
 * Checks if a given array is sorted ([i] < [i+1]).
 *
 * @param array Input array
 * @param length Length of the input array
 * @return true if the array is sorted; otherwise false
 */
bool check_sorted_sequence(int *array, int length) {
    // Check array element by element. Instantly abort if error was found.
    for (int i = 1; i < length; i++)
        if (array[i - 1] > array[i]) return false;

    // Seems to be a well-sorted array. Congrats!
    return true;
}


/**
 * Sorts a given array using the merge-sort algorithm.
 *
 * @param array Input array
 * @param help A helper array that must be at least as long as the input array
 * @param length Length of the input array
 */
void merge_sort(int *array, int *help, unsigned length) {
    // Check if the given array consists only out of one element -> return then
    if (length == 1)
        return;

    // -> Array obviously contains more than one element
    // Divide into two (more or less) equal sized parts
    unsigned left_array_length = length / 2;
    unsigned right_array_length = left_array_length + length % 2;

    int *left_array = array;
    int *right_array = array + left_array_length;

    int *left_array_help = help;
    int *right_array_help = help + left_array_length;

    // Sort both parts using recursion
    // Last task will be created when
    #pragma omp task
        merge_sort(left_array, left_array_help, left_array_length);
    #pragma omp task
        merge_sort(right_array, right_array_help, right_array_length);
    #pragma omp taskwait

    // Both parts are obviously sorted now
    // Merge both parts into one
    merge_sort_sort(array, help, left_array_length, right_array_length);
}


/**
 * Merges two part-sorted arrays to one. Both arrays must be memory-neighbors.
 *
 * @param array Pointer to a part-sorted array / left array
 * @param left_array_length Length of the left array. Beginning at given array position and ending after specified length.
 * @param right_array_length Length of the right array. Beginning after the left array length and ending after specified length.
 * @param help Pointer to a helper array. Needs to be at least as long as total length.
 */
void merge_sort_sort(int *array, int *help, unsigned left_array_length, unsigned right_array_length) {
    int *left_array = array, *right_array = array + left_array_length;
    int totalLength = left_array_length + right_array_length;

    // Initialize position vars for merging (iterators for left/right array)
    int it_left = 0, it_right = 0;

    for (int i = 0; i < totalLength; i++) {
        // Reached end of left array? Start copying right array.
        if (it_left == left_array_length) {
            // Set current output element and move input pointer forward.
            help[i] = right_array[it_right++];
            continue;
        }

        // Reached end of right array? Start copying left array.
        if (it_right == right_array_length) {
            // Set current output element and move input pointer forward.
            help[i] = left_array[it_left++];
            continue;
        }

        // Compare elements at their current pointer position
        // NOTE: Right array elements will always be preferred if equal
        if (left_array[it_left] < right_array[it_right]) {
            // Left array element is smaller. Copy to output array and move pointer forward.
            help[i] = left_array[it_left++];
        } else {
            // Right array element is smaller / equal. Copy to output array and move pointer forward.
            help[i] = right_array[it_right++];
        }
    }

    // Copy helper array back to main array
    for (int i = 0; i < totalLength; i++)
        array[i] = help[i];
}
