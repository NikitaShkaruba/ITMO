#include <iostream>
#include <fstream>
#include "sortAlgorithms/Algorithms.h"
#include "memoryManagers/FileMapper.h"

using namespace std;

/* A call to mmap( ) asks the kernel to map len bytes of the object represented by the file descriptor fd,
 * starting at offset bytes into the file, into memory. If addr is included, it indicates a preference to
 * use that starting address in memory. The access permissions are dictated by prot,
 * and additional behavior can be given by flags.
 *
 * void* mmap (void *addr,
               size_t len,
               int prot,
               int flags,
               int fd,
               off_t offset);
 * I don't think that other methods needs an explanation
 */
void testFileMapping() {
    FileMapper mm;

    // single allocation test
    int* s = (int *) mm.alloc(sizeof(int));

    cout << "Current single int is:" << *s << endl;
    *s += 2;
    cout << "after change single int is:" << *s << endl << endl;

    mm.free(s, sizeof(int));


    // array allocation test
    double* array = (double *) mm.alloc(sizeof(double) * 5);

    for (int i = 0; i < 5; ++i) {
        cout << "array[" << i << "] before change is =" << array[i] << endl;
        array[i] = 2;
        cout << "array[" << i << "] after change is =" << array[i] << endl << endl;
    }

    mm.free(array, sizeof(double) * 5);
}

bool is_file_exist(const char *fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}
void generateFileWithIntegers(size_t intAmount) {
    ofstream outStream("randomNumbers.txt", ios::out);

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
    ofstream outStream(filename);

    for(vector<int>::iterator it = integers.begin(); it != integers.end(); it++)
        outStream << *it << endl;
}

int main() {
    if (!is_file_exist("randomNumbers.txt"))
        generateFileWithIntegers(100500/4);

    vector<int> integers = getIntegersFromFile("randomNumbers.txt");
    // MergeSort(&integers.front(), integers.size());       works!
    // MergeSortFM(&integers.front(), integers.size());     works!
    MergeSortBP(&integers.front(), integers.size());
    writeIntegersToFile(integers, "sortedNumbers.txt");
}