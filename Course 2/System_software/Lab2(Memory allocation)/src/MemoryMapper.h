#pragma once

#include <glob.h>
#include <vector>
#include <stdint.h>
#include <limits.h>

using namespace std;

const size_t MAPPED_BYTES_AMOUNT = INT_MAX;

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

