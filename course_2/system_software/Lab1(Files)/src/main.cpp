#include "copyFunctions.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 4) {
        string key = argv[1];
        string inPath = argv[2];
        string outPath = argv[3];

        if (key == "--posix" || key == "-x")
            posixCopy(inPath, outPath);

        if (key == "--language" || key == "-l")
            customCopy(inPath, outPath);

        if (key == "--sendfile" || key == "-s")
            sendfileCopy(inPath, outPath);

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
            cout << "Usage pattern for dummies: 'cp --pretty in.txt out.txt'" << endl;
            cout << "Available keys: " << endl;
            cout << "\t --posix -x" << endl;
            cout << "\t --language -l" << endl;
            cout << "\t --sendfile -s" << endl;
            cout << "\t --pretty -p" << endl;
            return 0;
        }
    }

    cout << "Wrong arguments. Try 'Lab1_cp_ --help' for help" << endl;
    return 0;
}
