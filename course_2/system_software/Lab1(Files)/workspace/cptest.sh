#!/bin/bash

# tput - program for chaning output text color
# If you want to use this script for testing your custom program, do these things:
#	* Create file in.txt with your grades following this pattern "Shkaruba 3 Algorithms_and_data_structures 99.14"
#	* Set propriate path for your executable(Change /home/nikita... to your path)

# ----------------------- grades table tests ------------------------ #
tput setaf 1; 
echo "1) Testing custom cp copying grades-table"
tput sgr0 

echo ""
echo "/home/nikita/.CLion12/system/cmake/generated/b6f317f6/b6f317f6/Debug/cp --posix in.txt out.txt"
/home/nikita/.CLion12/system/cmake/generated/b6f317f6/b6f317f6/Debug/cp --posix in.txt out.txt
echo "out.txt's content is: "
cat out.txt
rm out.txt

echo ""
echo ""
echo "/home/nikita/.CLion12/system/cmake/generated/b6f317f6/b6f317f6/Debug/cp --language in.txt out.txt"
/home/nikita/.CLion12/system/cmake/generated/b6f317f6/b6f317f6/Debug/cp --language in.txt out.txt
echo "out.txt's content is: "
cat out.txt
rm out.txt

echo ""
echo "/home/nikita/.CLion12/system/cmake/generated/b6f317f6/b6f317f6/Debug/cp --sendfile in.txt out.txt"
/home/nikita/.CLion12/system/cmake/generated/b6f317f6/b6f317f6/Debug/cp --sendfile in.txt out.txt
echo "out.txt's content is: "
cat out.txt
rm out.txt

# ------------------------- large file tests --------------------------- #
echo ""
echo ""
tput setaf 1; 
echo "2) Testing custom pc by large files"
tput setaf 2; 
echo "generating large file named largeIn"
dd if=/dev/zero of=largeIn count=1024 bs=262144
tput sgr0;

echo ""
echo "The number of seconds before {posix} copy is `date +%s`."
echo "/home/nikita/.CLion12/system/cmake/generated/b6f317f6/b6f317f6/Debug/cp --posix largeIn largeOut"
/home/nikita/.CLion12/system/cmake/generated/b6f317f6/b6f317f6/Debug/cp --posix largeIn largeOut
echo $"The number of seconds after {posix} copy is `date +%s`."
rm largeOut

echo ""
echo "The number of seconds before {language-level} is `date +%s`."
echo "/home/nikita/.CLion12/system/cmake/generated/b6f317f6/b6f317f6/Debug/cp --language largeIn largeOut"
/home/nikita/.CLion12/system/cmake/generated/b6f317f6/b6f317f6/Debug/cp --language largeIn largeOut
echo "The number of seconds after {language-level} is `date +%s`."
rm largeOut

echo ""
echo "The number of seconds before {sendfile copy} is `date +%s`."
echo "/home/nikita/.CLion12/system/cmake/generated/b6f317f6/b6f317f6/Debug/cp --sendfile largeIn largeOut"
/home/nikita/.CLion12/system/cmake/generated/b6f317f6/b6f317f6/Debug/cp --sendfile largeIn largeOut
echo "The number of seconds after {sendfile copy} is `date +%s`."
rm largeOut
rm largeIn
