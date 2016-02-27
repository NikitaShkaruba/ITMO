#include <iostream>
#include <sys/sendfile.h>
#include <fstream>
#include <vector>
#include "copyFunctions.h"

ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
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

int main(int argc, char* argv[]) {
    if (argc == 4) {
        string key = argv[1];
        string inPath = argv[2];
        string outPath = argv[3];

        if (isNotEnableToOpenFile(inPath)) {
            cout << "Can't open file :(";
            return 0;
        }

        // retrieving handles and etc..
        if (key == "--system" || key == "-s") {

        }
        // simple programming way
        if (key == "--language" || key == "-l") {
            cppCopy(inPath, outPath);
        }
        // alternative to windows's copyFile
        if (key == "--sendfile") {

        }
        if (key == "--pretty" || key == "-p") {
            ifstream  src("in.txt", std::ios::binary);
            ofstream  dst("out.txt", std::ios::binary);

            dst << src.rdbuf();
        }

        return 0;
    }
    if (argc == 2) {
        string key = argv[1];

        if (key == "--help" || key == "-h") {
            cout << "::HELP::" << endl;
            cout << "Usage pattern for dummies: 'Lab1_cp_ --pretty in.txt out.txt'" << endl;
            cout << "Available keys: " << endl;
            cout << "\t --system -s" << endl;
            cout << "\t --language -l" << endl;
            cout << "\t --sendfile" << endl;
            cout << "\t --pretty -p" << endl;
            return 0;
        }
    }

    cout << "Wrong arguments. Try 'Lab1_cp_ --help' for help" << endl;
    return 0;
}
