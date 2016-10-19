#include <iostream>
#include <zconf.h>
#include <semaphore.h>
#include <semaphore.h>
using namespace std;


int* arr;
int arr_size;
uint sleep_time;

pthread_t* threadIds = new pthread_t[2];
sem_t semaphore;
int sort_pivot = -1;

void* work(void* args) {
    cout << "Input sleep time after each element is processed: ";
    cin >> sleep_time;

    for (int i = 0; i < arr_size; i++) {
        sem_wait(&semaphore);

        int min = i;
        for(int j = i+1; j < arr_size; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
            int buf = arr[min];
            arr[min] = arr[i];
            arr[i] = buf;
            sort_pivot++;
        }

        cout << "Sleeping";
        sleep(sleep_time);
        sem_post(&semaphore);
        sleep(100);
    }
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
    sem_init(&semaphore, 1, 1);

    cout << "array's size: ";
    cin >> arr_size;

    arr = new int[arr_size];
    cout << "Input " << arr_size <<" elements now" << endl;
    for(int i = 0; i <  arr_size; i++) {
        cout << "arr[" << i << "] = ";
        cin >> arr[i];
    }

    pthread_create(&(threadIds[0]), NULL, &work, NULL);
    // pthread_create(&(threadIds[1]), NULL, &multiplyElements, NULL);

    while(sort_pivot != arr_size - 1) {
        sem_wait(&semaphore);
        if (sort_pivot != -1) {
            cout << arr[sort_pivot] << ", ";
        }
        sem_post(&semaphore);
    }

    return 0;
}
