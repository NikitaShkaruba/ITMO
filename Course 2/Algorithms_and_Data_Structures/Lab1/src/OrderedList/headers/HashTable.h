#pragma once

#include <string>
#include <vector>
#include "OrderedList.h"

using namespace std;

class HashTable {
public:
    HashTable();

    void insert(string content);
    bool find(string content) const ;
    int hash(string word) const;
    void printTree() const;
    float getAverageCollisionCount() const;
    long getAverageAccessTimeInMilliseconds() const;

private:
    void restructure();

    OrderedList* buckets;
    int entriesCount;
    int bucketsCount;
    const int criticalLoadFactor = 7;
};

