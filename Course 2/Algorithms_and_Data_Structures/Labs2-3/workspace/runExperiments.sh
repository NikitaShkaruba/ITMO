#!/bin/bash

SECONDS=0 # built in constant which increments

touch timestamp1.txt
for verticesAmount in {10..10000..100} do
	./GraphAlgorithms run --algorithm dijkstra --directed 1 -va $verticesAmount -ea $($verticesAmount*$verticesAmount/10) -min 1 -max 1000000 --start 0 --finish $($verticesAmount-1)
	printf "vertex amount: %s\texecution time: %s\n" "$SECONDS" "$verticesAmount" >> timestamp1.txt
done
