#!/bin/bash
for threads in 2 4 8 16
do
	for chunk in 1 10 100 1000 10000 100000 1000000
	do
		echo -n "$threads,$chunk,"
		env OMP_NUM_THREADS=$threads ./taskd 100000000 $chunk
		echo ""
	done
done
