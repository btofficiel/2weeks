/* Expected output
Error found in thread: 1
Error found in thread: 3
Error found in thread: 2
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

pthread_key_t error_key;

void init_error();
void free_error(void *value);
void set_thread_error(const char *msg);
const char* get_thread_error();
void thread_func(int *id);

int main() {
    int thread_ids[3] = {1,2,3};
    pthread_t threads[3];

    pthread_once_t error_key_init = PTHREAD_ONCE_INIT;
    pthread_once(&error_key_init, (void *) init_error);

    for(int i=0;i<3;i++) {
        pthread_create(&threads[i], NULL, (void *) thread_func, &thread_ids[i]);
    }

    for(int i=0;i<3;i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void init_error() {
    pthread_key_create(&error_key, (void *) free_error);
}

void free_error(void *value) {
    free(value);
}

void set_thread_error(const char *msg) {
    char* error = strdup(msg);
    pthread_setspecific(error_key, (void *) error);
}

const char* get_thread_error() {
    void *value = pthread_getspecific(error_key);
    return value ? (const char*) value : "No error";
}

void thread_func(int *id) {
    char msg[30];
    snprintf(msg, sizeof(msg), "Error found in thread: %d\n", *id);
    set_thread_error(msg);
    const char* value = get_thread_error();
    printf("%s", value);
}
