#include <string>
#include "headers/CodeParser.h"

using namespace std;

void CodeParser::retrieveWordsFromFile(string file) {
    ifstream inputStream(file, ios::in);
    string word;

    while (inputStream >> word) {
        words.insert(word);
    }

    inputStream.close();
}

void CodeParser::printHashTableInfo() {
    cout << "::INFO::" << endl;

    cout << "Average collission count: " << words.getAverageCollisionCount() << endl;
    cout << "Average find time: " << words.getAverageAccessTimeInMilliseconds() << " milliseconds" << endl;

    words.printTree();
}
