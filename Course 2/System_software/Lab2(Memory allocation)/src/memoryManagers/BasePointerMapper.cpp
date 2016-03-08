#include <stdio.h>
#include "BasePointerMapper.h"

BasePointerMapper::BasePointerMapper(size_t bytesAmount) {
    base = new char[bytesAmount];
    isAllocated.insert(isAllocated.begin(), bytesAmount, false);
}
BasePointerMapper::~BasePointerMapper() {
    delete[] base;
}

void *BasePointerMapper::alloc(size_t bytesAmount) {
    int currentByteCounter = 0;

    for (int i = 0; i < isAllocated.size(); ++i) {
        if (!isAllocated[i]) {
            currentByteCounter++;

            if (currentByteCounter == bytesAmount) {
                for (int j = i - bytesAmount + 1; j <= i; j++)
                    isAllocated[j] = true;

                return base + i - bytesAmount + 1;
            }
        } else {
            currentByteCounter = 0;
        }
    }

    perror("Not enough memory");
}
void BasePointerMapper::free(void *ptr, size_t bytesAmount) {
    int startIndex = (int) (((char*)ptr - base) / sizeof(char));

    for (int i = startIndex; i < startIndex + bytesAmount; ++i) {
        isAllocated[i] = false;
    }
}
