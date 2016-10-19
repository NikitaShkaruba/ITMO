#include <iostream>
#include <zconf.h>
using namespace std;

int* arr;
int arr_size;
uint sleep_time;

void* work(void* args) {
    // lock semaphore

    cout << "Input sleep time after each element is processed: ";
    cin >> sleep_time;

    // sort elements, when element i is ready - send it to main
    // release mutex
    return 0;
}

void* multiplyElements(void* args) {
    int result = 1;
    for (int i = 0; i < arr_size; i++) {
        result *= arr[i];
        sleep(sleep_time);
    }

    cout << "Element's multiplication is: " << result;
    return 0;
}

// 3.12
int main() {
    cout << "OS. Lab 3" << endl;

    cout << "array's size: ";
    cin >> arr_size;

    arr = new int[arr_size];
    cout << "Input " << arr_size <<" elements now" << endl;
    for(int i = 0; i <  arr_size; i++) {
        cout << "arr[" << i << "] = ";
        cin >> arr[i];
    }

    // Run work in new thread
    // Run multiplyElement in new thread

    return 0;
}