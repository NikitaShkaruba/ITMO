#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <semaphore.h>
#include <sys/types.h>

using namespace std;

// Synchronization objects
static pthread_mutex_t cs_mutex =  PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
pthread_mutex_t mutex;
sem_t semaphore;
pthread_cond_t conditionVariable;
static pthread_mutex_t condMutex = PTHREAD_MUTEX_INITIALIZER;

// CS stands for "critical section"
void* sortAndFindCS(void *args) {
    pthread_mutex_lock( &cs_mutex );

    printf("Thread with PID %d processing\n", pthread_self());
    sleep(1);
    printf("Thread finished\n");

    pthread_mutex_unlock( &cs_mutex );
}
void* sortAndFindMutex(void *args) {
    pthread_mutex_lock(&mutex);

    printf("Thread with PID %d processing\n", pthread_self());
    sleep(1);
    printf("Thread finished\n");

    pthread_mutex_unlock(&mutex);
}
void* sortAndFindSemaphore(void *args) {
    sem_wait(&semaphore);

    printf("Thread with PID %d processing\n", pthread_self());
    sleep(1);
    printf("Thread finished\n");

    sem_post(&semaphore);
}
// I dunno why, but this piece of shit works every 2nd time, haha :D I thing that i'm forgetting about some resource :/
void* sortAndFindConditionVariable(void* args) {
    pthread_mutex_lock(&condMutex);
    pthread_cond_wait(&conditionVariable, &condMutex);

    printf("Thread with PID %d had waited his turn\n", pthread_self());
    sleep(1);
    printf("Thread finished processing\n");

    pthread_cond_signal(&conditionVariable);
    pthread_mutex_unlock(&condMutex);
}

int main(void) {
    pthread_t threadIds[3];

    // Critical sections
    printf("****Testing critical sections****\n");

    pthread_create(&(threadIds[0]), NULL, &sortAndFindCS, NULL);
    pthread_create(&(threadIds[1]), NULL, &sortAndFindCS, NULL);
    pthread_create(&(threadIds[2]), NULL, &sortAndFindCS, NULL);

    sleep(5);

    // Mutex
    printf("****Testing mutex synchronization****\n");
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&(threadIds[0]), NULL, &sortAndFindMutex, NULL);
    pthread_create(&(threadIds[1]), NULL, &sortAndFindMutex, NULL);
    pthread_create(&(threadIds[2]), NULL, &sortAndFindMutex, NULL);

    sleep(5);
    pthread_mutex_destroy(&mutex);

    // Semaphore
    printf("****Testing semaphore synchronization****\n");
    sem_init(&semaphore, 1, 2); // create semaphore with capasity of 2

    pthread_create(&(threadIds[0]), NULL, &sortAndFindSemaphore, NULL);
    pthread_create(&(threadIds[1]), NULL, &sortAndFindSemaphore, NULL);
    pthread_create(&(threadIds[2]), NULL, &sortAndFindSemaphore, NULL);

    sleep(5);
    sem_destroy(&semaphore);

    // Events
    printf("****Testing event synchronization****\n");
    pthread_cond_init(&conditionVariable, NULL);

    pthread_create(&(threadIds[0]), NULL, &sortAndFindConditionVariable, NULL);
    pthread_create(&(threadIds[1]), NULL, &sortAndFindConditionVariable, NULL);
    pthread_create(&(threadIds[2]), NULL, &sortAndFindConditionVariable, NULL);

    // notify a locked thread
    pthread_cond_signal(&conditionVariable);

    sleep(10);
    pthread_cond_destroy(&conditionVariable);

    return 0;
}

