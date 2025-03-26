#include <stdio.h>
#include <pthread.h>

pthread_once_t log_init_once = PTHREAD_ONCE_INIT;

void log_init();
void log_msg(int* id);
void thread_func(int* id);

int main() {
    int thread_ids[3] = {1,2,3};
    pthread_t threads[3];

    for(int i=0;i<3;i++){
        pthread_create(&threads[i], NULL, (void *) thread_func, &thread_ids[i]);
    }

    for(int i=0;i<3;i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

// Will only run once
void log_init() {
    printf("------Logger initialised------\n");
}

void log_msg(int *id) {
    pthread_once(&log_init_once, (void *) log_init);
    printf("Thread ID: %d logging...\n", *id);
}

void thread_func(int *id) {
    log_msg(id);
}

