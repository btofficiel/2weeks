/* Expected output
------Logger initialised------
Thread ID: 3 logging...
Thread ID: 2 logging...
Thread ID: 1 logging...
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_once_t log_init_once = PTHREAD_ONCE_INIT;

void log_init();
void log_msg(int* id);
void thread_func(int* id);

int main() {
    int thread_ids[3] = {1,2,3};
    pthread_t threads[3];
    pthread_attr_t attrs[3];
    struct sched_param params[3];

    for(int i=0;i<3;i++){
        pthread_attr_init(&attrs[i]);
        pthread_attr_setscope(&attrs[i], PTHREAD_SCOPE_PROCESS);
        pthread_attr_setinheritsched(&attrs[i], PTHREAD_EXPLICIT_SCHED);
        pthread_attr_setschedpolicy(&attrs[i], SCHED_FIFO);
        params[i].sched_priority = thread_ids[i];
        pthread_attr_setschedparam(&attrs[i], &params[i]);
        pthread_create(&threads[i], &attrs[i], (void *) thread_func, &thread_ids[i]);
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

