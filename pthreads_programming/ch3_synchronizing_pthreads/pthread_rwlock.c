#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 5
#define MAX_COUNT 101

pthread_rwlock_t rwlock;
pthread_cond_t max_count_reached_cv = PTHREAD_COND_INITIALIZER;
int data = 0;

// Reader writer prototypes
void reader(int *idp);
void writer();

int main() {
    // Reader IDs
    int reader_ids[NUM_READERS] = { 1, 2, 3, 4, 5 };
    
    // Initialise read-write lock
    pthread_rwlock_init(&rwlock, NULL);

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

    pthread_rwlock_destroy(&rwlock);

    return 0;
}

void reader(int *idp) {
    int id = *idp;
    while(1) {
        pthread_rwlock_rdlock(&rwlock);
        printf("Reader ID: %d, Reading Data: %d\n", id, data);
        if(data == MAX_COUNT) {
            pthread_rwlock_unlock(&rwlock);
            break;
        }
        pthread_rwlock_unlock(&rwlock);
        usleep(100000);
    }
}

void writer() {
    while(1) {
        pthread_rwlock_wrlock(&rwlock);
        if(data == MAX_COUNT) {
            pthread_rwlock_unlock(&rwlock);
            break;
        }
        data++;
        printf("Writer writing data: %d\n", data);
        pthread_rwlock_unlock(&rwlock);
        usleep(100000);
    }
}


        



