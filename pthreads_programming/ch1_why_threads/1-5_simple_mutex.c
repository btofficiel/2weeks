#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void do_one_thing(int *);
void do_another_thing(int *);
void do_wrap(int, int);

int r1 =0;
int r2=0;
int r3=0;
//  declare and initialize a mutex
pthread_mutex_t r3_mutex=PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv) {
     struct timespec start, end;
    // Start the timer
    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_t thread1, thread2;

    r3 = atoi(argv[1]);

    pthread_create(&thread1, NULL, (void *) do_one_thing, (void *) &r1);
    pthread_create(&thread2, NULL, (void *) do_another_thing, (void *) &r2);

    // Wait for the thread to finish and retrieve its return value
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    do_wrap(r1, r2);

    // Stop the timer
    clock_gettime(CLOCK_MONOTONIC, &end);
    // Calculate the elapsed time in seconds
    double elapsed_time = (end.tv_sec - start.tv_sec) + 
                          (end.tv_nsec - start.tv_nsec) * 1e-9;
    // Print the elapsed time
    printf("\nElapsed time: %f seconds\n", elapsed_time);

    return 0;
}

void do_one_thing(int *pnum_times) {
    int i,j,x;

    pthread_mutex_lock(&r3_mutex);
    if(r3 >0) {
        x= r3;
        r3--;
    } else {
        x = 1;
    }
    pthread_mutex_unlock(&r3_mutex);

    for(i = 0; i < 4; i++) {
        printf("doing one thing\n");
        for(j=0; j < 10000; j++) x = x+i;
        (*pnum_times)++;
    }
}

void do_another_thing(int *pnum_times) {
    int i,j,x;

    pthread_mutex_lock(&r3_mutex);
    if(r3 >0) {
        x= r3;
        r3--;
    } else {
        x = 1;
    }
    pthread_mutex_unlock(&r3_mutex);
    for(i = 0; i < 4; i++) {
        printf("doing another thing\n");
        for(j=0; j < 10000; j++) x = x+i;
        (*pnum_times)++;
    }
}

void do_wrap(int one_times, int another_times) {
    int total;

    total = one_times+another_times;
    printf("wrap up: one thing %d, another %d, total %d\n", one_times, another_times, total);
}
