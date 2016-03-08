#include "Algorithms.h"
#include "../memoryManagers/BasePointerMapper.h"
#include "../memoryManagers/FileMapper.h"

template<typename T> T* getSubArrayCopy(T *arr, size_t count) {
    // Complexity: O(1)
    // coz T(n) = O(count) = O(1)
    T* result = new T[count];

    for (size_t i = 0; i < count; i++)		// count*
        result[i] = arr[i];

    return result;
}
void MergeSort(int* arr, size_t size) {
    // Complexity O(n*log(n))
    if (size == 1)
        return;

    MergeSort(arr, size/2);
    MergeSort(arr + size/2, size - size/2);

    int l = 0, r = (int) (size / 2);	// left and right indexes respectively
    int* buf = getSubArrayCopy(arr, size);

    for (size_t i = 0; i < size; i++) {			// O(n)
        if (l != size/2 && r != size)
            arr[i] = buf[l] < buf[r] ? buf[l++] : buf[r++];
        else
            arr[i] = (l != size/2) ? buf[l++] : buf[r++];
    }
    delete[] buf;
}

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
void MergeSortFM(int* arr, size_t size) {
    static FileMapper fileMapper(size*5); // fucking shit gdb, good god, can some1 debug it for me, coz i fucking cant.
    if (size == 1)
        return;

    MergeSortFM(arr, size/2);
    MergeSortFM(arr + size/2, size - size/2);

    int l = 0, r = (int) (size / 2);	// left and right indexes respectively

    // getSubbarray()
    int* buf = (int*) fileMapper.alloc(sizeof(int) * size);
    for (size_t i = 0; i < size; i++)		// count*
        buf[i] = arr[i];

    for (size_t i = 0; i < size; i++) {			// O(n)
        if (l != size/2 && r != size)
            arr[i] = buf[l] < buf[r] ? buf[l++] : buf[r++];
        else
            arr[i] = (l != size/2) ? buf[l++] : buf[r++];
    }

    fileMapper.free(buf, sizeof(int) * size);
}

void MergeSortBP(int* arr, size_t size) {
    static BasePointerMapper pointerMapper(size*5); // * 5 because of fragmentation error, and i can't debug it coz GDB IS FUCKING PIECE OF CRAP. Damn, i am insane coz of gdb.
    if (size == 1)
        return;

    MergeSortBP(arr, size/2);
    MergeSortBP(arr + size/2, size - size/2);

    int l = 0, r = (int) (size / 2);	// left and right indexes respectively

    // getSubbarray()
    int* buf = (int*) pointerMapper.alloc(sizeof(int) * size);
    for (size_t i = 0; i < size; i++)		// count*
        buf[i] = arr[i];

    for (size_t i = 0; i < size; i++) {			// O(n)
        if (l != size/2 && r != size)
            arr[i] = buf[l] < buf[r] ? buf[l++] : buf[r++];
        else
            arr[i] = (l != size/2) ? buf[l++] : buf[r++];
    }

    pointerMapper.free(buf, sizeof(int) * size);
}
