#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include<unistd.h>


//Static initialisation of a mutex
pthread_mutex_t add_lock = PTHREAD_MUTEX_INITIALIZER;
//Total counter
int total = 0;

void add(int);
void worker(int *arg);

int main() {
    pthread_t t1;
    pthread_t t2;

    int t1_value = 7;
    int t2_value = 10;

    pthread_create(&t1, NULL, (void *) worker, (void *) &t1_value);
    pthread_create(&t2, NULL, (void *) worker, (void *) &t2_value);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Will print either 7 or 10: %d\n", total);

    return 0;
}

void add(int value) {
    // We are checking for three states here
    // 1) 0 -> This means we successfully acquired the lock 
    // 2) EBUSY -> Some other thread has the lock currency
    // 3) Else -> Some error occurred
    int lock_status = pthread_mutex_trylock(&add_lock);
    if(lock_status == 0) {
        total += value;
        usleep(100000); // Add 100ms delay
        pthread_mutex_unlock(&add_lock);
    } else if (lock_status == EBUSY) {
        printf("Cannot add %d, resource already locked\n", value);
    } else {
        printf("Error, could not acquire lock due to some issue\n");
    }
}

void worker(int *arg) {
    add(*arg);
}

