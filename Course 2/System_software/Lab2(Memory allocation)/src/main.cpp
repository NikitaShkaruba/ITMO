#include <iostream>
#include <fstream>
#include "sortAlgorithms/Algorithms.h"
#include "memoryManagers/FileMapper.h"

using namespace std;

bool is_file_exist(const char *fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}

void generateFileWithIntegers(size_t intAmount) {
    ofstream outStream("randomNumbers.txt");

    for (int i = 0; i < intAmount; ++i)
        outStream << "" << rand() << endl;

    outStream.close();
}
vector<int> getIntegersFromFile(string filename) {
    ifstream inStream(filename);
    vector<int> integers;

    string integer;
    while(inStream >> integer) {
        integers.push_back(stoi(integer));
    }

    return integers;
}
void writeIntegersToFile(vector<int> integers, string filename) {
    ofstream outStream(filename, fstream::out | fstream::trunc);

    for(vector<int>::iterator it = integers.begin(); it != integers.end(); it++)
        outStream << *it << endl;
}

void printHelp() {
    cout << "Usage pattern: sort --file-mapping in.txt out.txt" << endl << endl;

    cout << "Available memory mapping methods: " << endl;
    cout << "\t --file-mapping, -f : use file mapping memory managment " << endl;
    cout << "\t --pointer-mappint -p" << endl;
    cout << "\t --heap -h" << endl;
    cout << "Optional keys: " << endl;
    cout << "\t --generate-integers -g {intAmount} : generate test file" << endl;
    cout << "\t --help : print help" << endl;
}
int main(int argc, char* argv[]) {
    string key = argv[1];

    switch(argc) {
        case 2:
            if (key == "--help") {
                printHelp();
                return 0;
            } else {
                cout << "Wrong arguments. Try sort -help" << endl;
                return 1;
            }
        case 3:
            if (key == "--generate-integers" || key == "-g") {
                int intAmount = stoi(argv[2]);
                if (!is_file_exist("randomNumbers.txt"))
                    generateFileWithIntegers(intAmount);
                return 0;
            } else {
                cout << "Wrong arguments. Try sort -help" << endl;
                return 1;
            }
        case 4: {
            string inName = argv[argc - 2];
            vector<int> integers = getIntegersFromFile(inName);

            if (key == "--file-mapped" || key == "-f")
                MergeSortFM(&integers.front(), integers.size());
            else if (key == "--pointer-mapped" || key == "-p")
                MergeSortBP(&integers.front(), integers.size());
            else if (key == "--heap" || key == "-h")
                MergeSort(&integers.front(), integers.size());
            else {
                cout << "Wrong arguments. Try sort -help" << endl;
                return 1;
            }

            string outName = argv[argc - 1];
            writeIntegersToFile(integers, outName);
            return 0;
        }
        default:
            cout << "Wrong arguments. Try sort -help" << endl;
            return 1;
    }
}