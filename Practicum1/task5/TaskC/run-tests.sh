#!/bin/bash
for threads in 1 2 4 8 16
do
		echo -n "$threads,"
		env OMP_NUM_THREADS=$threads ./taskc -2 2 -2 2 50
		echo ""
done
