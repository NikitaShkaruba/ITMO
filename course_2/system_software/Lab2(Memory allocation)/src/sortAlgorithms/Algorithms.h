#pragma once

#include <stddef.h>
#include <stdlib.h>

// Simple heap memory usage method
void MergeSort(int* arr, size_t size);
void QuickSort(int* arr, size_t size);

// File mapping memory usage method
void MergeSortFM(int* arr, size_t size);
void QuickSortFM(int* arr, size_t size);

// Base pointer memory usage method
void MergeSortBP(int* arr, size_t size);
void QuickSortBP(int* arr, size_t size);
