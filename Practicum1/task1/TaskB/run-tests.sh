#!/bin/bash
for threads in 2 4 8 16
do
	for chunk in 1 10 100 1000 10000 100000 1000000
	do
		echo "Threads: $threads / Chunksize: $chunk"
		echo "-------------------------------------"
		env OMP_NUM_THREADS=$threads ./taskb 100000000 $chunk
		echo ""
		echo ""
		echo ""
	done
done
