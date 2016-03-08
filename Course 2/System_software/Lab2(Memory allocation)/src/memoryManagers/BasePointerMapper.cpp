#include <stdio.h>
#include "BasePointerMapper.h"

BasePointerMapper::BasePointerMapper() {
    base = new char[100500];
    isAllocated.insert(isAllocated.begin(), 100500, false);
}
BasePointerMapper::~BasePointerMapper() {
    delete[] base;
}

void *BasePointerMapper::alloc(size_t byteAmount) {
    int currentByteCounter = 0;

    for (int i = 0; i < isAllocated.size(); ++i) {
        if (!isAllocated[i]) {
            currentByteCounter++;

            if (currentByteCounter == byteAmount) {
                for (int j = i - byteAmount + 1; j <= i; j++)
                    isAllocated[j] = true;

                return base + i - byteAmount + 1;
            }
        } else {
            currentByteCounter = 0;
        }
    }

    perror("Not enough memory");
}
void BasePointerMapper::free(void *ptr, size_t byteAmount) {
    int startIndex = (int) (((char*)ptr - base) / sizeof(char));

    for (int i = startIndex; i < startIndex + byteAmount; ++i) {
        isAllocated[i] = false;
    }
}
