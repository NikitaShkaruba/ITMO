#include "CodeParser.h"

using namespace std;

bool isNotEnableToOpenFile(string filename) {
    ifstream inputStream(filename, ios::in);
    if (!inputStream.is_open()) {
        inputStream.close();
        return true;
    } else {
        inputStream.close();
        return false;
    }
}

// Hash function: Sum of first and second ASCII-codesУпорядоченный   список   с   логарифмическим
// Collision resolved by: log(n) organized list
int main(int argc, char* argv[]) {
    CodeParser parser;

    if (argc == 1 || isNotEnableToOpenFile(argv[1]))
        return 1;

    parser.retrieveWordsFromFile(argv[1]);
    // TODO: add logic
}


