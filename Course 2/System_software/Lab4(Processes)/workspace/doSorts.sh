#!/bin/bash

tput setaf 1; 
echo "0) Generating 100500 integers in file randomNumbers.txt"
tput sgr0
rm -rf randomNumbers.txt
touch randomNumbers.txt
for i in `seq 1 100500`; do
    echo $RANDOM >> randomNumbers.txt
done

tput setaf 1;
echo "1) head randomNumbers.txt"
tput sgr0
head randomNumbers.txt

tput setaf 1; 
echo "2) Running SortAndFind program:"
tput sgr0
./SortAndFind --sort-algorithm quick --missed-number 1230 randomNumbers.txt
