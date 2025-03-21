#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define T_COUNT 10
#define WATCH_COUNT 12

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t count_threshhold_cv = PTHREAD_COND_INITIALIZER;
int count = 0;
int thread_ids[3] = {1, 2, 3};

void watch_count(int*);
void increment_count(int*);

int main() {
    pthread_t t1, t2, wc;

    pthread_create(&t1, NULL, (void *) increment_count, &thread_ids[0]);
    pthread_create(&t2, NULL, (void *) increment_count, &thread_ids[1]);
    pthread_create(&wc, NULL, (void *) watch_count, &thread_ids[2]);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(wc, NULL);


    return 0;
}

void watch_count(int *idp) {
    pthread_mutex_lock(&count_mutex);

    while(count < WATCH_COUNT) {
        pthread_cond_wait(&count_threshhold_cv, &count_mutex);
        printf("Thread: %d, Count: %d\n", *idp, count);
    }

    pthread_mutex_unlock(&count_mutex);
}

void increment_count(int *idp) {
    for(int i=0;i<T_COUNT;i++) {
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Thread: %d, Old count: %d, New Count: %d\n", *idp, count-1, count);
        if(count == WATCH_COUNT) pthread_cond_signal(&count_threshhold_cv);
        pthread_mutex_unlock(&count_mutex);
    }
}




