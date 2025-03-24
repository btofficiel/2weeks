#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "rdwr.h"

#define NUM_READERS 5
#define MAX_COUNT 101

pthread_rdwr_t rwlock;
pthread_cond_t max_count_reached_cv = PTHREAD_COND_INITIALIZER;
int data = 0;

// Reader writer prototypes
void reader(int *idp);
void writer();

int main() {
    // Reader IDs
    int reader_ids[NUM_READERS] = { 1, 2, 3, 4, 5 };
    
    // Initialise read-write lock
    pthread_rdwr_init_np(&rwlock);

    // Declare readers and writer
    pthread_t readers[NUM_READERS];
    pthread_t t_writer;

    
    pthread_create(&t_writer, NULL, (void *) writer, NULL);

    for(int i=0; i<NUM_READERS;i++) {
        pthread_create(&readers[i], NULL, (void *) reader, (void *) &reader_ids[i]);
    }

    pthread_join(t_writer, NULL);

    for(int i=0;i< NUM_READERS;i++) {
        pthread_join(readers[i], NULL);
    }

    pthread_rdwr_destroy_np(&rwlock);

    return 0;
}

void reader(int *idp) {
    int id = *idp;
    while(1) {
        pthread_rdwr_rlock_np(&rwlock);
        printf("Reader ID: %d, Reading Data: %d\n", id, data);
        if(data == MAX_COUNT) {
            pthread_rdwr_runlock_np(&rwlock);
            break;
        }
        pthread_rdwr_runlock_np(&rwlock);
        usleep(100000);
    }
}

void writer() {
    while(1) {
        pthread_rdwr_wlock_np(&rwlock);
        if(data == MAX_COUNT) {
            pthread_rdwr_wunlock_np(&rwlock);
            break;
        }
        data++;
        printf("Writer writing data: %d\n", data);
        pthread_rdwr_wunlock_np(&rwlock);
        usleep(100000);
    }
}
