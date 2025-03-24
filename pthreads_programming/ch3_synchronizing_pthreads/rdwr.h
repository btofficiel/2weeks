#ifndef RDWR_H
#define RDWR_H

#include <pthread.h>

typedef struct rdwr_var {
    int readers_reading;
    int writers_writing;
    pthread_mutex_t mutex;
    pthread_cond_t lock_free;
} pthread_rdwr_t;

int pthread_rdwr_init_np(pthread_rdwr_t* rdwrp);
int pthread_rdwr_destroy_np(pthread_rdwr_t* rdwrp);
int pthread_rdwr_rlock_np(pthread_rdwr_t* rdwrp);
int pthread_rdwr_wlock_np(pthread_rdwr_t* rdwrp);
int pthread_rdwr_runlock_np(pthread_rdwr_t* rdwrp);
int pthread_rdwr_wunlock_np(pthread_rdwr_t* rdwrp);

#endif
