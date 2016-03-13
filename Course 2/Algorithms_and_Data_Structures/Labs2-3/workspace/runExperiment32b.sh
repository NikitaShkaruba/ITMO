#!/bin/bash 

if [ ! -d "./timestamps" ]; then
	mkdir timestamps
	mkdir timestamps/dijkstra
	mkdir timestamps/bellmanford
fi

# ------------- 3.2.b ------------- #
# verticesAmount: iterable
# edgesAmount: 1000*verticesAmount
# minWeight: 1; maxWeight: 10^6

tput setaf 1; 
echo "Experiment 3.2.b"
tput sgr0 

minWeight=1
maxWeight=1000000

> timestamps/dijkstra/dijkstra-32b.txt
> timestamps/bellmanford/bellmanford-32b.txt

for ((verticesAmount = 101; verticesAmount < (10**4)+1; verticesAmount += 100))
do
	edgesAmount=$[1000*verticesAmount]

	SECONDS=0 
	./GraphAlgorithms run --algorithm dijkstra --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1] | tee -a timestamps/dijkstra/dijkstra-32b.txt | more
	printf "vertices amount: %s\texecution time: %s\n" "$verticesAmount" "$SECONDS" | tee -a timestamps/dijkstra/dijkstra-32b.txt | more

	SECONDS=0 
	./GraphAlgorithms run --algorithm bellman-ford --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1] | tee -a timestamps/bellmanford/bellmanford-32b.txt | more
	printf "vertices amount: %s\texecution time: %s\n" "$verticesAmount" "$SECONDS" | tee -a timestamps/bellmanford/bellmanford-32b.txt | more
done

