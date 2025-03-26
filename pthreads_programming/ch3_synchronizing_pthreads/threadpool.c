#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "threadpool.h"
#define MAX_THREADS 10
#define MAX_TASKS 100


int main() {
    srand(time(0));

    ThreadPool *tpp = (ThreadPool*) malloc(sizeof(ThreadPool));
    
    threadpool_init(tpp);

    int task_args[MAX_TASKS];

    for(int i=0;i<MAX_TASKS;i++) {
        task_args[i] = rand() % 9001 + 1000;
        threadpool_add_task(tpp, (void *) print_task, &task_args[i]);
    }

    sleep(5);
    threadpool_shutdown(tpp);

    return 0;
}

void worker(ThreadPool *pool) {
    while(1) {
        pthread_mutex_lock(&(pool->mutex));
        while(pool->task_count == 0 && !pool->shutdown) {
            pthread_cond_wait(&(pool->signal), &(pool->mutex));
        }

        if(pool->shutdown && pool->task_count == 0) {
            pthread_mutex_unlock(&(pool->mutex));
            break;
        }

        Task t = pool->tasks[pool->task_head];
        pool->task_head = (pool->task_head+1)%pool->max_tasks;
        pool->task_count--;
        pthread_mutex_unlock(&(pool->mutex));
        t.fn(t.arg);
    }
}

void print_task(void *arg) {
    int *payload = (int *) arg;
    printf("Thread - %llu executing task - %d\n", (unsigned long long) pthread_self(), *payload);
}

void threadpool_init(ThreadPool *pool) {
    pool->max_tasks = MAX_TASKS;
    pool->task_head = 0;
    pool->task_tail = 0;
    pool->shutdown = false;
    pool->task_count = 0;

    pool->threads = (pthread_t*) malloc(sizeof(pthread_t)*MAX_THREADS);
    pool->tasks = (Task*) malloc(sizeof(Task)*MAX_TASKS);

    for(int i=0;i<MAX_THREADS;i++) {
        pthread_create(&pool->threads[i], NULL, (void*) worker, pool);
    }

    pthread_mutex_init(&(pool->mutex), NULL);
    pthread_cond_init(&(pool->signal), NULL);
}

int threadpool_add_task(ThreadPool* pool, void (*fn)(void *arg), void *arg) {
    pthread_mutex_lock(&(pool->mutex));
    if(pool->task_count == pool->max_tasks) {
        pthread_mutex_unlock(&(pool->mutex));
        return -1;
    }

    pool->tasks[pool->task_tail].fn = fn;
    pool->tasks[pool->task_tail].arg = arg;
    // Keep rotating in a circular way
    pool->task_tail  = (pool->task_tail+1)%pool->max_tasks;
    pool->task_count++;

    pthread_cond_signal(&(pool->signal));
    pthread_mutex_unlock(&(pool->mutex));

    return 0;
}

int threadpool_shutdown(ThreadPool *pool) {
    pthread_mutex_lock(&(pool->mutex));
    pool->shutdown = true;
    pthread_cond_broadcast(&(pool->signal));
    pthread_mutex_unlock(&(pool->mutex));

    for(int i=0;i<MAX_THREADS;i++) {
        pthread_join(pool->threads[i], NULL);
    }

    free(pool->threads);
    free(pool->tasks);
    pthread_cond_destroy(&(pool->signal));
    pthread_mutex_destroy(&(pool->mutex));
    free(pool);
    return 0;
}
    






