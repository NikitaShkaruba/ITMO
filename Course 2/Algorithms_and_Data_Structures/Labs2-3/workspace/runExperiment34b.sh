#!/bin/bash 

if [ ! -d "./timestamps" ]; then
	mkdir timestamps
	mkdir timestamps/dijkstra
	mkdir timestamps/bellmanford
fi

# ------------- 3.4.b ------------- #
# verticesAmount: 10^4+1
# edgesAmount: 1000*verticesAmount
# minWeight: 1; maxWeight: iterable

tput setaf 1; 
echo "Experiment 3.4.b"
tput sgr0 

verticesAmount=10001
edgesAmount=$[1000*verticesAmount]
minWeight=1

> timestamps/dijkstra/dijkstra-34b.txt
> timestamps/bellmanford/bellmanford-34b.txt
echo $edgesAmount

for ((maxWeight = 1; maxWeight < 200; maxWeight++))
do
	SECONDS=0 
	./GraphAlgorithms run --algorithm dijkstra --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1] | tee -a timestamps/dijkstra/dijkstra-34b.txt  | more
	printf "max weight: %s\texecution time: %s\n" "$maxWeight" "$SECONDS" | tee -a timestamps/dijkstra/dijkstra-34b.txt | more

	SECONDS=0 
	./GraphAlgorithms run --algorithm bellman-ford --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1] | tee -a timestamps/bellmanford/bellmanford-34b.txt | more
	printf "max weight: %s\texecution time: %s\n" "$maxWeight" "$SECONDS" | tee -a timestamps/bellmanford/bellmanford-34b.txt | more
done
