#include <stdio.h>
#include <sys/mman.h>
#include <sys/file.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include "FileMapper.h"

FileMapper::FileMapper() {
    isAllocated.insert(isAllocated.begin(), MAPPED_BYTES_AMOUNT, false);
    MapMemoryToFile();
}
FileMapper::~FileMapper() {
    if (munmap(start, MAPPED_BYTES_AMOUNT) == -1)
        perror ("munmap fails");
}

void FileMapper::MapMemoryToFile() {
    int fd = open("FileToMap.fmobj", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1)
        perror("Opening of mapped file fails");
    else
        fillFile(fd);

    start = (char*) mmap (0, MAPPED_BYTES_AMOUNT, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    if (start == MAP_FAILED)
        perror("mmap fails");
    close(fd);
}
void* FileMapper::alloc(size_t byteAmount) {
    int currentByteCounter = 0;

    assert(byteAmount > 0);

    for (int i = 0; i < isAllocated.size(); ++i) {
        if (!isAllocated[i]) {
            currentByteCounter++;

            if (currentByteCounter == byteAmount) {
                for (int j = i - byteAmount + 1; j <= i; j++)
                    isAllocated[j] = true;

                return start + i - byteAmount + 1;
            }
        } else {
            currentByteCounter = 0;
        }
    }

    perror("Not enough memory");
}
void FileMapper::free(void *ptr, size_t byteAmount) {
    int startIndex = (int) (((char*)ptr - start) / sizeof(char));

    for (int i = startIndex; i < startIndex + byteAmount; ++i) {
        isAllocated[i] = false;
    }
}

// I need this function, because i can't borrow memory from empty file
void FileMapper::fillFile(int fd) {
    ftruncate(fd, MAPPED_BYTES_AMOUNT);
}
