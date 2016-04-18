#include <iostream>
#include <chrono>
#include <assert.h>
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

bool HashTable::find(string content) const {
    return buckets[hash(content)].find(content);
}

int HashTable::hash(string word) const {
    return rand() % bucketsCount;
}
    /* switch(word.size()) {
        case 0: throw "Word have no _size";
        case 1: return word[0] % bucketsCount;
        default: return (word[0]+word[1]) % bucketsCount;
    }
} */

void HashTable::restructure() {
    OrderedList* oldBuckets = buckets;
    int oldBucketsCount = bucketsCount;

    bucketsCount *= 2;
    entriesCount = 0;
    buckets = new OrderedList[bucketsCount];

    for (int i = 0; i < oldBucketsCount; i++) {
        for (int j = 0; j < oldBuckets[i].size(); j++) {
            buckets->insert(oldBuckets[i][j]);
        }
    }

    delete[] oldBuckets;
}

void HashTable::printTree() const {
    cout << endl << "HashTable tree:";

    for (int i = 0; i < bucketsCount; ++i) {
        cout << endl << i << ") ";
        for (int j = 0; j < buckets[i].size(); ++j) {
            cout << " <===> {" << buckets[i][j] << "}";
        }
    }
}

float HashTable::getAverageCollisionCount() const {
    float result = 0;
    int collissionedRows = 0;

    for (int i = 0; i < bucketsCount; ++i) {
        if (buckets[i].size() > 1) {
            collissionedRows++;
            result += buckets[i].size() - 1;
        }
    }
    
    return result / collissionedRows;
}

long HashTable::getAverageAccessTimeInMilliseconds() const {
    vector<string> stringsToFind;

    for (int i = 0; i < bucketsCount; ++i) {
        for (int j = 0; j < buckets[i].size(); ++j) {
            stringsToFind.push_back(buckets[i][j]);
        }
    }

    using namespace std::chrono;
    milliseconds allDuration;
    for (int i = 0; i < stringsToFind.size(); ++i) {
        milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
        allDuration += duration_cast< milliseconds >(system_clock::now().time_since_epoch()) - ms;
    }

    return allDuration.count();
}
