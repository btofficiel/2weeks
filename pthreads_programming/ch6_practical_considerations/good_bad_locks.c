#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct timespec start_bad, end_bad, start_good, end_good;

void badlock_func(void* arg) {
    clock_gettime(CLOCK_MONOTONIC, &start_bad);
    
    pthread_mutex_lock(&mutex);
    
    FILE* fp = fopen("./5k_words.txt", "a");
    if (fp == NULL) {
        printf("Badlock: Error opening file!\n");
    } else {
        fprintf(fp, "Badlock was here\n");
        fclose(fp);
    }
    
    count++;
    printf("Badlock: Count = %d\n", count);
    
    pthread_mutex_unlock(&mutex);
    
    clock_gettime(CLOCK_MONOTONIC, &end_bad);
}

void goodlock_func(void* arg) {
    clock_gettime(CLOCK_MONOTONIC, &start_good);
    
    pthread_mutex_lock(&mutex);
    
    count++;
    printf("Goodlock: Count = %d\n", count);
    
    pthread_mutex_unlock(&mutex);
    
    clock_gettime(CLOCK_MONOTONIC, &end_good);
}

double calculate_time_diff(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
}

int main() {
    pthread_t badlock, goodlock;
    
    if (pthread_create(&goodlock, NULL, (void*) goodlock_func, NULL) != 0) {
        printf("Error creating goodlock thread\n");
        return 1;
    }

    if (pthread_create(&badlock, NULL, (void*) badlock_func, NULL) != 0) {
        printf("Error creating badlock thread\n");
        return 1;
    }
    
    pthread_join(badlock, NULL);
    pthread_join(goodlock, NULL);
    
    double time_bad = calculate_time_diff(start_bad, end_bad);
    double time_good = calculate_time_diff(start_good, end_good);
    
    printf("\nResults:\n");
    printf("Badlock lock hold time: %.2f nanoseconds\n", time_bad);
    printf("Goodlock lock hold time: %.2f nanoseconds\n", time_good);
    printf("Final count value: %d\n", count);
    
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
