#pragma once

#include <glob.h>
#include <vector>

using namespace std;

class BasePointerMapper {
public:
    BasePointerMapper();
    ~BasePointerMapper();

    void*alloc(size_t size);
    void free(void *ptr, size_t byteAmount);

private:
    vector<bool> isAllocated;
    char* base;
};
