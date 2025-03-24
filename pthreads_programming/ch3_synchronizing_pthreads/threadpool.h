#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include <stdbool.h>

typedef struct _task {
    void (*fn)(void*);
    void *arg;
} Task;

typedef struct _threadpool {
    pthread_t *threads;
    Task *tasks;
    int task_head;
    int task_tail;
    int task_count;
    int max_tasks;
    pthread_mutex_t mutex;
    pthread_cond_t signal;
    bool shutdown;
} ThreadPool;

void worker(ThreadPool *pool);
void print_task(void *arg);
void threadpool_init(ThreadPool* pool);
int threadpool_add_task(ThreadPool *pool, void (*fn)(void *arg), void *arg);
int threadpool_shutdown(ThreadPool *pool);


#endif


