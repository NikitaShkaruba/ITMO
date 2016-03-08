#!/bin/bash 

if [ ! -d "./timestamps" ]; then
	mkdir timestamps
	mkdir timestamps/dijkstra
	mkdir timestamps/bellmanford
fi

# ------------- 3.4.a ------------- #
# verticesAmount: 10^4+1
# edgesAmount: verticesAmount^2
# minWeight: 1; maxWeight: iterable

tput setaf 1; 
echo "Experiment 3.4.a"
tput sgr0 

verticesAmount=10001
edgesAmount=$[verticesAmount^2]
minWeight=1

> timestamps/dijkstra/dijkstra-34a.txt
> timestamps/bellmanford/bellmanford-34a.txt

for maxWeight in {1..200..1}
do
	SECONDS=0 
	./GraphAlgorithms run --algorithm dijkstra --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1] >> timestamps/dijkstra/dijkstra-34a.txt
	printf "max weight: %s\texecution time: %s\n" "$maxWeight" "$SECONDS" >> timestamps/dijkstra/dijkstra-34a.txt

	SECONDS=0 
	./GraphAlgorithms run --algorithm bellman-ford --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1] >> timestamps/bellmanford/bellmanford-34a.txt
	printf "max weight: %s\texecution time: %s\n" "$maxWeight" "$SECONDS" >> timestamps/bellmanford/bellmanford-34a.txt
done

