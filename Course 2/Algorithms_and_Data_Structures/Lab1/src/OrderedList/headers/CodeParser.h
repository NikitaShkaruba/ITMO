#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "HashTable.h"

// builder class
class CodeParser {
public:
    void retrieveWordsFromFile(string filename);

private:
    HashTable words;
};

