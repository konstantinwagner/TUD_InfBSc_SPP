#include <cstdio>
#include "../komplex.h"
#include "../ppmwrite.h"
#include <cstdlib>
#include <omp.h>

int iterate(double x, double y, int maxIter);

const int minNorm = 16;

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Invalid argument counter\n");
        printf("Required format: <command> <xmin> <xmax> <ymin> <ymax> <maxIter>\n");
        return -1;
    }

    // Parse args
    // Format: <command> <xmin> <xmax> <ymin> <ymax> <maxIter>
    double xmin = atof(argv[1]);
    double ymin = atof(argv[3]);
    double xmax = atof(argv[2]);
    double ymax = atof(argv[4]);
    int maxIter = atoi(argv[5]);

    // Starting timer (includes: step calculation & field calculation)
    double needed_time = omp_get_wtime();

    // Calculate step size -> difference between _min and _max
    double xStep = (xmax - xmin) / width;
    double yStep = (ymax - ymin) / width;

    field mdb;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            mdb[x][y] = iterate(x * xStep + xmin, y * yStep + ymin, maxIter);
        }
    }

    // Stop timer & print out time
    needed_time = omp_get_wtime() - needed_time;
    printf("Finished after %f seconds!\n", needed_time);

    // Write result to bitmap file -> not included in time measurement
    ppmwrite("out.ppm", mdb, maxIter);

    return 0;
}


/**
 * Returns needed iterations of a given point on mandelbrot field
 *
 * @param x Position's x value
 * @param y Position's y value
 * @param maxIter Maximum iterations counter (-> return <= maxIter)
 * @return Number of needed iteration steps
 */
int iterate(double x, double y, int maxIter) {
    // Declare complex vars
    komplex z = komplex(0, 0);
    komplex c = komplex(x, y);

    // Do iteration steps!
    int i = 0;
    while (i < maxIter && z.norm() < minNorm) {
        z.mult(&z);
        z.add(&c);
        i++;
    }

    // Return iteration counter -> mandelbrot field!!111!
    return i;
}
