#include <stdio.h>
#include <pthread.h>

void *return_error();

static const int internal_error = 500;

int main() {
    pthread_t thread;
    
    void *statusup;

    pthread_create(&thread, NULL, (void *) return_error, NULL);

    pthread_join(thread, &statusup);

    if(statusup == PTHREAD_CANCELED) {
        printf("Thread exited with PTHREAD_CANCELED status\n");
    } else {
        printf("Thread exited with status: %d\n", *((int *)statusup));
    }

    return 0;
}

void *return_error() {
    // pthread_exit((void *) &internal_error); could be an alternative
    return ((void *) &internal_error);
}
