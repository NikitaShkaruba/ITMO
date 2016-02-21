#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "OrderedList/headers/HashTable.h"

using namespace std;

// builder class
class CodeParser {
public:
    void retrieveWordsFromFile(string file);

private:
    HashTable words;
};

