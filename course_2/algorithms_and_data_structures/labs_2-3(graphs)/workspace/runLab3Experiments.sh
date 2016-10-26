#!/bin/bash 

if [ ! -f "./GraphAlgorithms" ]; then
	echo "Cannot find GraphAlgorithms executable in current directory ^("
	exit 1
fi
if [ ! -d "./timestamps" ]; then
	mkdir timestamps
fi

# clear existing files or create them if they're missing
> timestamps/prim-31a.txt
> timestamps/prim-31b.txt
> timestamps/kruskal-31a.txt
> timestamps/kruskal-31b.txt

#-------------- 3.1.a ---------------#
# verticesAmount: iterable
# edgesAmount: (verticesAmount^2)/10
# minWeight: 1; maxWeight: 10^6

tput setaf 1; 
echo "Experiment 3.1.a"
tput sgr0 

minWeight=1
maxWeight=$[10**6]

for ((verticesAmount = 1; verticesAmount < (10**4)+1; verticesAmount += 100))
do
	edgesAmount=$[(verticesAmount**2)/10]

	printf "\nGenerated vertices amount: %s\nGenerated edges amount: %s\n" "$verticesAmount" "$edgesAmount" | tee -a timestamps/prim-31a.txt | more
	./GraphAlgorithms run --algorithm prim --directed 0 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight | tee -a timestamps/prim-31a.txt | more

	printf "\nGenerated vertices amount: %s\nGenerated edges amount: %s\n" "$verticesAmount" "$edgesAmount" | tee -a timestamps/kruskal-31a.txt | more
	./GraphAlgorithms run --algorithm kruskal --directed 0 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight | tee -a timestamps/kruskal-31a.txt | more
done

# ---------- 3.1.b ----------- #
# verticesAmount: iterable
# edgesAmount: verticesAmount^2
# minWeight: 1; maxWeight: 10^6

tput setaf 1; 
echo "Experiment 3.1.b"
tput sgr0 

minWeight=1
maxWeight=$[10**6]

for ((verticesAmount = 1; verticesAmount < (10**4)+1; verticesAmount += 100))
do
	edgesAmount=$[verticesAmount**2]

	printf "\nGenerated vertices amount: %s\nGenerated edges amount: %s\n" "$verticesAmount" "$edgesAmount" | tee -a timestamps/prim-31b.txt | more
	./GraphAlgorithms run --algorithm prim --directed 0 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight | tee -a timestamps/prim-31b.txt | more

	printf "\nGenerated vertices amount: %s\nGenerated edges amount: %s\n" "$verticesAmount" "$edgesAmount" | tee -a timestamps/kruskal-31b.txt | more
	./GraphAlgorithms run --algorithm kruskal --directed 0 -va $verticesAmount -ea $edgesAmount -min $minWeight -max $maxWeight | tee -a timestamps/kruskal-31b.txt | more
done
