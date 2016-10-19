#pragma once

#include <glob.h>
#include <vector>
#include <stdint.h>
#include <limits.h>

using namespace std;

class FileMapper {
public:
    FileMapper(size_t i);
    ~FileMapper();

    void*alloc(size_t size);
    void free(void *ptr, size_t size);

private:
    void MapMemoryToFile();

    vector<bool> isAllocated;
    char* start;    // start of mapped memory
};

