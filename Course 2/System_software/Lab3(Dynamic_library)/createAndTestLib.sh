#!/bin/bash

echo "0) compiling src to objects";
gcc -fPIC -g -c -Wall src/libsrc/LibraryIOFunctions.c
gcc -fPIC -g -c -Wall src/libsrc/LibraryMathFunctions.c

echo "1) creating lib";
gcc -shared -fPIC -Wl,-soname,libcrap.so.1 -o libcrap.so.1.5.0 LibraryMathFunctions.o LibraryIOFunctions.o -lc

echo "2) removing .o files"
rm *.o

echo "3) creating symbolic link"
ldconfig -n .

echo "4) compiling source files with custom and math library-links"
gcc src/main.c libcrap.so.1.5.0 -lm -o thirdPartyProgram # -lm is needed for sin and cos functions, coz 

echo "5) adding library to dynamic linkage variable, so it can be found "
export LD_LIBRARY_PATH=$PWD

echo "6) executing output file"
./thirdPartyProgram
