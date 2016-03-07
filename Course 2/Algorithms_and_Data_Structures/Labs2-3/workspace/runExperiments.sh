#!/bin/bash 
# My script for Lab 2 algorithm experiments

mkdir timestamps
mkdir timestamps/dijkstra
mkdir timestamps/bellmanford

#--------------------------------------- 3.1 --------------------------------------#
minWeight=1
maxWeight=1000000

# 3.1.a
# verticesAmount: iterable
# edgesAmount: (verticesAmount^2)/10
# minWeight: 1; maxWeight: 10^6
tput setaf 1; 
echo "Experiment 3.1.a"
tput sgr0 

> timestamps/dijkstra/dijkstra-31a.txt
> timestamps/bellmanford/bellmanford-31a.txt

for verticesAmount in {1..10001..100}
do
	edgesAmount=$[verticesAmount^2/10]

	SECONDS=0 # built in bash constant which auto-increments
	./GraphAlgorithms run --algorithm dijkstra --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1]
	printf "vertices amount: %s\texecution time: %s\n" "$verticesAmount" "$SECONDS" >> timestamps/dijkstra/dijkstra-31a.txt

	SECONDS=0 
	./GraphAlgorithms run --algorithm bellman-ford --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1]
	printf "vertices amount: %s\texecution time: %s\n" "$verticesAmount" "$SECONDS" >> timestamps/bellmanford/bellmanford-31a.txt
done

# 3.1.b
# verticesAmount: iterable
# edgesAmount: verticesAmount^2
# minWeight: 1; maxWeight: 10^6
tput setaf 1; 
echo "Experiment 3.1.b"
tput sgr0 

> timestamps/dijkstra/dijkstra-31b.txt
> timestamps/bellmanford/bellmanford-31b.txt

for verticesAmount in {1..10001..100}
do
	edgesAmount=$[verticesAmount^2]

	SECONDS=0 
	./GraphAlgorithms run --algorithm dijkstra --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1]
	printf "vertices amount: %s\texecution time: %s\n" "$verticesAmount" "$SECONDS" >> timestamps/dijkstra/dijkstra-31b.txt

	SECONDS=0 
	./GraphAlgorithms run --algorithm bellman-ford --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1]
	printf "vertices amount: %s\texecution time: %s\n" "$verticesAmount" "$SECONDS" >> timestamps/bellmanford/bellmanford-31b.txt
done

#--------------------------------------- 3.2 --------------------------------------#
minWeight=1
maxWeight=1000000

# 3.2.a
# verticesAmount: iterable
# edgesAmount: 100*verticesAmount
# minWeight: 1; maxWeight: 10^6
tput setaf 1; 
echo "Experiment 3.2.a"
tput sgr0 

> timestamps/dijkstra/dijkstra-32a.txt
> timestamps/bellmanford/bellmanford-32a.txt

for verticesAmount in {101..10001..100}
do
	edgesAmount=$[100*verticesAmount]

	SECONDS=0 
	./GraphAlgorithms run --algorithm dijkstra --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1]
	printf "vertices amount: %s\texecution time: %s\n" "$verticesAmount" "$SECONDS" >> timestamps/dijkstra/dijkstra-32a.txt

	SECONDS=0 
	./GraphAlgorithms run --algorithm bellman-ford --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1]
	printf "vertices amount: %s\texecution time: %s\n" "$verticesAmount" "$SECONDS" >> timestamps/bellmanford/bellmanford-32a.txt
done

# 3.2.b
# verticesAmount: iterable
# edgesAmount: 1000*verticesAmount
# minWeight: 1; maxWeight: 10^6
tput setaf 1; 
echo "Experiment 3.2.b"
tput sgr0 

> timestamps/dijkstra/dijkstra-32b.txt
> timestamps/bellmanford/bellmanford-32b.txt

for verticesAmount in {101..10001..100}
do
	edgesAmount=$[1000*verticesAmount]

	SECONDS=0 
	./GraphAlgorithms run --algorithm dijkstra --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1]
	printf "vertices amount: %s\texecution time: %s\n" "$verticesAmount" "$SECONDS" >> timestamps/dijkstra/dijkstra-32b.txt

	SECONDS=0 
	./GraphAlgorithms run --algorithm bellman-ford --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1]
	printf "vertices amount: %s\texecution time: %s\n" "$verticesAmount" "$SECONDS" >> timestamps/bellmanford/bellmanford-32b.txt
done

#------------------------------- 3.3 ------------------------------#
verticesAmount=10001
minWeight=1
maxWeight=1000000

# 3.3
# verticesAmount: 10^4+1
# edgesAmount: iterable
# minWeight: 1; maxWeight: 10^6
tput setaf 1; 
echo "Experiment 3.3"
tput sgr0 

> timestamps/dijkstra/dijkstra-33.txt
> timestamps/bellmanford/bellmanford-33.txt

for edgesAmount in {0..10000000..100000}
do
	SECONDS=0 
	./GraphAlgorithms run --algorithm dijkstra --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1]
	printf "edges amount: %s\texecution time: %s\n" "$edgesAmount" "$SECONDS" >> timestamps/dijkstra/dijkstra-33.txt

	SECONDS=0 
	./GraphAlgorithms run --algorithm bellman-ford --directed 1 -va 10001 -ea $edgesAmount -min 1 -max 1000000 --start 0 --finish $10000
	printf "edges amount: %s\texecution time: %s\n" "$edgesAmount" "$SECONDS" >> timestamps/bellmanford/bellmanford-33.txt
done

#------------------------------- 3.4 ------------------------------#
verticesAmount=10001
minWeight=1


# 3.4.a
# verticesAmount: 10^4+1
# edgesAmount: verticesAmount^2
# minWeight: 1; maxWeight: iterable
tput setaf 1; 
echo "Experiment 3.4.a"
tput sgr0 

edgesAmount=$[verticesAmount^2]
> timestamps/dijkstra/dijkstra-34a.txt
> timestamps/bellmanford/bellmanford-34a.txt

for maxWeight in {1..200..1}
do
	SECONDS=0 
	./GraphAlgorithms run --algorithm dijkstra --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1]
	printf "max weight: %s\texecution time: %s\n" "$maxWeight" "$SECONDS" >> timestamps/dijkstra/dijkstra-34a.txt

	SECONDS=0 
	./GraphAlgorithms run --algorithm bellman-ford --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1]
	printf "max weight: %s\texecution time: %s\n" "$maxWeight" "$SECONDS" >> timestamps/bellmanford/bellmanford-34a.txt
done

# 3.4.b
# verticesAmount: 10^4+1
# edgesAmount: 1000*verticesAmount
# minWeight: 1; maxWeight: iterable
tput setaf 1; 
echo "Experiment 3.4.b"
tput sgr0 

edgesAmount=$[1000*verticesAmount]
> timestamps/dijkstra/dijkstra-34b.txt
> timestamps/bellmanford/bellmanford-34b.txt

for maxWeight in {1..200..1}
do
	SECONDS=0 
	./GraphAlgorithms run --algorithm dijkstra --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1]
	printf "max weight: %s\texecution time: %s\n" "$maxWeight" "$SECONDS" >> timestamps/dijkstra/dijkstra-34b.txt

	SECONDS=0 
	./GraphAlgorithms run --algorithm bellman-ford --directed 1 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight --start 0 --finish $[verticesAmount-1]
	printf "max weight: %s\texecution time: %s\n" "$maxWeight" "$SECONDS" >> timestamps/bellmanford/bellmanford-34b.txt
done
