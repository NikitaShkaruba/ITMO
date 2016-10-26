#!/bin/bash

tput setaf 1; 
echo "Generating 100500 integers"
tput sgr0 
./sort --generate-integers 100500
echo "Integers to sort head:"
head randomNumbers.txt

tput setaf 1; 
echo "0) Using standart c++ heap dynamic memory" 
tput sgr0 
./sort --heap randomNumbers.txt out1.txt
echo "Resulted file head:"
head out1.txt

tput setaf 1; 
echo "1) Using file-mapped dynamic memory" 
tput sgr0 
./sort --file-mapped randomNumbers.txt out2.txt
echo "Resulted file head:"
head out2.txt

tput setaf 1; 
echo "0) Using base pointer mapped dynamic memory" 
tput sgr0 
echo "Resulted file head:"
./sort --pointer-mapped randomNumbers.txt out3.txt
head out3.txt
