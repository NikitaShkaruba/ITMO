#!/bin/bash

if [ ! -d "./timestamps" ]; then
	mkdir timestamps
	mkdir timestamps/dijkstra
	mkdir timestamps/bellmanford
fi

# ------------- 3.3 ------------ #
# verticesAmount: 10^4+1
# edgesAmount: iterable
# minWeight: 1; maxWeight: 10^6

tput setaf 1; 
echo "Experiment 3.3"
tput sgr0 

verticesAmount=10001
minWeight=1
maxWeight=1000000

> timestamps/dijkstra/dijkstra-33.txt
> timestamps/bellmanford/bellmanford-33.txt

for ((edgesAmount = 0; edgesAmount < 10**7; edgesAmount += 10**5))
do
	SECONDS=0 
	./GraphAlgorithms run --algorithm dijkstra --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1] | tee -a timestamps/dijkstra/dijkstra-33.txt | more
	printf "edges amount: %s\texecution time: %s\n" "$edgesAmount" "$SECONDS" | tee -a timestamps/dijkstra/dijkstra-33.txt | more

	SECONDS=0 
	./GraphAlgorithms run --algorithm bellman-ford --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1] | tee -a timestamps/bellmanford/bellmanford-33.txt | more
	printf "edges amount: %s\texecution time: %s\n" "$edgesAmount" "$SECONDS" | tee -a timestamps/bellmanford/bellmanford-33.txt | more
done
