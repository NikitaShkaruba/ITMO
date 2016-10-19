#include <string>
#include "headers/CodeParser.h"

using namespace std;

void CodeParser::retrieveWordsFromFile(string file) {
    ifstream inputStream(file, ios::in);
    string word;

    int i = 0;
    while (inputStream >> word) {
        if (i++ == 103)
            cout << "sht";
        words.insert(word);
    }

    inputStream.close();
}

void CodeParser::printHashTableInfo() {
    cout << "::INFO::" << endl;

    cout << "Average collision count: " << words.getAverageCollisionCount() << endl;
    cout << "Average access time: " << words.getAverageAccessTimeInMilliseconds() << " milliseconds" << endl;

    words.printTree();
}
