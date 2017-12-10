#!/bin/bash
for arrsize in 10 100 1000 10000 100000 1000000
do
		echo "ArraySize: $arrsize"
		./exec 100000000 $arrsize
		echo ""
done
