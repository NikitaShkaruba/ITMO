//
// Created by nikita on 21.02.16.
//

#include "CodeParser.h"
void CodeParser::retrieveWordsFromFile(string file) {
    ifstream inputStream(file, ios::in);
    string word;

    while (inputStream >> word) {
        words.insert(hash(word), word);
    }

    inputStream.close();
}

int CodeParser::hash(string word) {
    switch(word.size()) {
        case 0: throw "Word have no size";
        case 1: return word[0];
        default: return word[0] + word[1];
    }
}
