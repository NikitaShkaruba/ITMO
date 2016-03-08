#pragma once

#include <glob.h>
#include <vector>

using namespace std;

const int MAPPED_BYTES_AMOUNT = 100500;

class MemoryMapper {
public:
    MemoryMapper();
    ~MemoryMapper();

    void*alloc(size_t size);
    void free(void *ptr, size_t size);

private:
    void MapMemoryToFile();
    void fillFile(int fd);

    vector<bool> isAllocated;
    char* start;    // start of mapped memory
};

