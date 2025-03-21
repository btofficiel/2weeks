#ifndef SHARED_MUTEX_H
#define SHARED_MUTEX_H

#include <pthread.h>
#define SHM_NAME "/myshm"
#define NUM_INCREMENTS 1000

typedef struct _shareddata {
    pthread_mutex_t mutex;
    int counter;
} SharedData;


#endif
