#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "HashTable.h"

class CodeParser {
public:
    void retrieveWordsFromFile(string filename);
    void printHashTableInfo();

private:
    HashTable words;
};

