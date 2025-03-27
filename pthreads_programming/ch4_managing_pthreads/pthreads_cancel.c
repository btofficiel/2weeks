#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3

int count = NUM_THREADS;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t init_done = PTHREAD_COND_INITIALIZER;

void ask_for_it();
void sitting_duck();
void bullet_proof();

int main() {
    int i;
    void *statusp;

    pthread_t threads[NUM_THREADS];

    pthread_create(&threads[0], NULL, (void *) ask_for_it, NULL);
    pthread_create(&threads[1], NULL, (void *) sitting_duck, NULL);
    pthread_create(&threads[2], NULL, (void *) bullet_proof, NULL);

    printf("main(): All threads created\n");

    // Wait for all threads to initialise
    pthread_mutex_lock(&lock);
    while(count != 0) {
        pthread_cond_wait(&init_done, &lock);
    }
    pthread_mutex_unlock(&lock);

    for(i=0;i<NUM_THREADS;i++) {
        pthread_cancel(threads[i]);
    }


    for(i=0;i<NUM_THREADS;i++){
        pthread_join(threads[i], &statusp);
        if(statusp == PTHREAD_CANCELED) {
            printf("main(): joined to thread %d, statusp=PTHREAD_CANCELLED\n", i);
        } else {
            printf("main(): joined to thread %d\n", i);
        }
    }

    printf("main(): All threads have finished\n");
    return 0;
}

void ask_for_it() {
    int i=0;
    printf("ask_for_it(): Thread entered\n");
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    pthread_mutex_lock(&lock);
    count--;
    pthread_mutex_unlock(&lock);
    printf("ask_for_it(): Thread initialized\n");
    pthread_cond_signal(&init_done);

    for(;;i++) {
        if(i%1000000==0) {
            printf("ask_for_it(): This is the cancellation point\n");
            pthread_testcancel();
        }
    }
}

void bullet_proof(){
    int i=0;
    printf("bullet_proof(): Thread entered\n");
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    pthread_mutex_lock(&lock);
    count--;
    pthread_mutex_unlock(&lock);
    printf("bullet_proof(): Thread initialized\n");
    pthread_cond_signal(&init_done);

    for(;;i++) {
        if(i%10000000000==0) {
            printf("bullet_proof(): You can't cancel me...\n");
        }
    }
}

void sitting_duck(){
    int i=0;
    printf("sitting_duck(): Thread entered\n");
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    pthread_mutex_lock(&lock);
    count--;
    pthread_mutex_unlock(&lock);
    printf("sitting_duck(): Thread initialized\n");
    pthread_cond_signal(&init_done);

    for(;;i++) {
        if (i%10000000000==0) {
            pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
            printf("sitting_duck(): You can't cancel here\n");
            pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
            pthread_testcancel();
        }
    }
}





