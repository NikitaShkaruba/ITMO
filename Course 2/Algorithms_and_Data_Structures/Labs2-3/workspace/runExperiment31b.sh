#!/bin/bash 

if [ ! -d "./timestamps" ]; then
	mkdir timestamps
	mkdir timestamps/dijkstra
	mkdir timestamps/bellmanford
fi

# ---------- 3.1.b ----------- #
# verticesAmount: iterable
# edgesAmount: verticesAmount^2
# minWeight: 1; maxWeight: 10^6

tput setaf 1; 
echo "Experiment 3.1.b"
tput sgr0 

minWeight=1
maxWeight=1000000

> timestamps/dijkstra/dijkstra-31b.txt
> timestamps/bellmanford/bellmanford-31b.txt

for ((verticesAmount = 1; verticesAmount < (10**4)+1; verticesAmount += 100))
do
	edgesAmount=$[verticesAmount**2]

	SECONDS=0 # built in bash constant which auto-increments
	./GraphAlgorithms run --algorithm dijkstra --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1] | tee -a timestamps/dijkstra/dijkstra-31b.txt | more
	printf "vertices amount: %s\texecution time: %s\n" "$verticesAmount" "$SECONDS" | tee -a timestamps/dijkstra/dijkstra-31b.txt | more

	SECONDS=0 
	./GraphAlgorithms run --algorithm bellman-ford --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1] | tee -a timestamps/bellmanford/bellmanford-31b.txt | more
	printf "vertices amount: %s\texecution time: %s\n" "$verticesAmount" "$SECONDS" | tee -a timestamps/bellmanford/bellmanford-31b.txt | more
done
