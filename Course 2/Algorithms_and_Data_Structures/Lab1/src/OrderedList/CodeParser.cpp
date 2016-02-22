#include "headers/CodeParser.h"
#include <string>

using namespace std;

void CodeParser::retrieveWordsFromFile(string file) {
    ifstream inputStream(file, ios::in);
    string word;

    while (inputStream >> word) {
        if (word == "ptr")
            cout << "It's him";
        words.insert(word);
    }

    inputStream.close();
}
