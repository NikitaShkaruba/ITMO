#pragma once

#include <glob.h>
#include <vector>

using namespace std;

class BasePointerMapper {
public:
    BasePointerMapper(size_t bytesAmount);
    ~BasePointerMapper();

    void*alloc(size_t bytesAmount);
    void free(void *ptr, size_t bytesAmount);

private:
    vector<bool> isAllocated;
    char* base;
};
