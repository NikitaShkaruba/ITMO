#pragma once

#include <string>
#include <vector>
#include "headers/OrderedList.h"

using namespace std;

class HashTable {
public:
    void insert(string content);
    bool find(string content);
    int hash(string word);

private:
    vector<OrderedList> rows;
};

