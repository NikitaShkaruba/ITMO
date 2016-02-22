#include "headers/HashTable.h"

HashTable::HashTable() {
    bucketsCount = 10;
    entriesCount = 0;
    buckets = new OrderedList[bucketsCount];
}

void HashTable::insert(string content) {
    if ((float)entriesCount / bucketsCount > criticalLoadFactor)
        restructure();

    int h = hash(content);
    int sizeBefore = buckets[h].size();

    buckets[h].insert(content);

    if (sizeBefore < buckets[h].size())
        entriesCount++;
}

bool HashTable::find(string content) {
    return buckets[hash(content)].find(content);
}

int HashTable::hash(string word) {
    switch(word.size()) {
        case 0: throw "Word have no _size";
        case 1: return word[0] / bucketsCount;
        default: return (word[0]+word[1]) / bucketsCount;
    }
}

void HashTable::restructure() {
    OrderedList* oldBuckets = buckets;
    int oldEntriesCount = entriesCount;

    bucketsCount *= 2;
    entriesCount = 0;
    buckets = new OrderedList[bucketsCount];

    for (int i = 0; i < oldEntriesCount; ++i) {
        for (int j = 0; j < oldBuckets[i].size(); j++)
            buckets->insert(oldBuckets[i][j]);
    }

    delete[] oldBuckets;
}
