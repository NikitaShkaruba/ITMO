#include <iosfwd>
#include <string>
#include "OrderedList/headers/CodeParser.h"

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

// Option № 3
// Hash function: Sum of first and second ASCII-codes
// Collision resolved by: log(n) organized list
int main(int argc, char* argv[]) {
    CodeParser parser;

    if (argc == 1 || isNotEnableToOpenFile(argv[1]))
        return 1;

    parser.retrieveWordsFromFile(argv[1]);
    parser.printHashTableInfo();
}

