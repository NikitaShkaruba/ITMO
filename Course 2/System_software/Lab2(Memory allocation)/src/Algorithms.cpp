#include "Algorithms.h"
#include "MemoryMapper.h"

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
void QuickSort(int* arr, size_t size) {
    // Complexity T(n) = O(n*log(n))
    if (size <= 1)
        return;

    // amazing not naive partition implementation
    int key = (int) (rand() % size), i = 1; // i points on pivot element
    swap(arr[0], arr[key]);
    for (size_t j = 1; j < size; j++) { // j points on unsorted element
        if (arr[j] < arr[0])
            swap(arr[i++], arr[j]);
    }
    swap(arr[0], arr[i-1]);

    QuickSort(arr, i-1);
    QuickSort(arr + i, size - i);
}

MemoryMapper memoryMapper;
void MergeSortFM(int* arr, size_t size) {
    // Complexity O(n*log(n))
    if (size == 1)
        return;

    MergeSort(arr, size/2);
    MergeSort(arr + size/2, size - size/2);

    int l = 0, r = (int) (size / 2);	// left and right indexes respectively

    // getSubbarray()
    int* buf = (int*) memoryMapper.alloc(sizeof(int) * size);
    for (size_t i = 0; i < size; i++)		// count*
        buf[i] = arr[i];

    for (size_t i = 0; i < size; i++) {			// O(n)
        if (l != size/2 && r != size)
            arr[i] = buf[l] < buf[r] ? buf[l++] : buf[r++];
        else
            arr[i] = (l != size/2) ? buf[l++] : buf[r++];
    }

    memoryMapper.free(buf, sizeof(int) * size);
}
void QuickSortFM(int* arr, size_t size) {

}

void MergeSortBP(int* arr, size_t size) {

}
void QuickSortBP(int* arr, size_t size) {

}
