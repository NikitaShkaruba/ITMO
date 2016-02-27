#pragma once

#include <iostream>

using namespace std;

void customCopy(string inPath, string outPath);
void posixCopy(string inPath, string outPath);
void sendfileCopy(string inPath, string outPath);
